/* HTTP GET Example using plain POSIX sockets

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "sdkconfig.h"
#include "driver/uart.h"
#include "driver/gpio.h"

/* Constants that aren't configurable in menuconfig */
#define WEB_SERVER "192.168.8.103"
#define WEB_PORT "3000"
#define WEB_PATH "/"
#define BUF_SIZE (1024)

static const char *TAG = "example";

static const char *REQUEST = "GET " WEB_PATH " HTTP/1.0\r\n"
                             "Host: " WEB_SERVER ":" WEB_PORT "\r\n"
                             "User-Agent: esp-idf/1.0 esp32\r\n"
                             "\r\n";

// char *POST_REQUEST = "POST / HTTP/1.0\r\n"
//                      "Host: 192.168.8.103:3000\r\n"
//                      "User-Agent: esp-idf/1.0 esp32\r\n"
//                      "Content-Type: image/jpeg\r\n"
//                      "Content-Length: %d\r\n"
//                      "\r\n"
//                      "%s";

static void http_get_task(void *pvParameters)
{
    const struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;
    struct in_addr *addr;
    int s, r;
    char recv_buf[64];

    //  check for GPIO input
    esp_rom_gpio_pad_select_gpio(GPIO_NUM_4);
    // set the direction as input
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_INPUT);

    esp_rom_gpio_pad_select_gpio(GPIO_NUM_2);
    // set the direction as output
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    while (1)
    {

        // gpio_set_level(GPIO_NUM_2, 1);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        // gpio_set_level(GPIO_NUM_2, 0);

        // read input value
        int input_val = gpio_get_level(GPIO_NUM_4);
        // printf("input val: %d\n", input_val);

        //  check for GPIO input
        if (input_val == 1)
        {
            // printf("input val: %d\n", input_val);
            gpio_set_level(GPIO_NUM_2, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            gpio_set_level(GPIO_NUM_2, 0);

            int err = getaddrinfo(WEB_SERVER, WEB_PORT, &hints, &res);

            if (err != 0 || res == NULL)
            {
                ESP_LOGE(TAG, "DNS lookup failed err=%d res=%p", err, res);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
                continue;
            }
            addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
            ESP_LOGI(TAG, "DNS lookup succeeded. IP=%s", inet_ntoa(*addr));

            s = socket(res->ai_family, res->ai_socktype, 0);
            if (s < 0)
            {
                ESP_LOGE(TAG, "... Failed to allocate socket.");
                freeaddrinfo(res);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
                continue;
            }
            ESP_LOGI(TAG, "... allocated socket");

            if (connect(s, res->ai_addr, res->ai_addrlen) != 0)
            {
                ESP_LOGE(TAG, "... socket connect failed errno=%d", errno);
                close(s);
                freeaddrinfo(res);
                vTaskDelay(4000 / portTICK_PERIOD_MS);
                continue;
            }

            ESP_LOGI(TAG, "... connected");
            freeaddrinfo(res);

            if (write(s, REQUEST, strlen(REQUEST)) < 0)
            {
                ESP_LOGE(TAG, "... socket send failed");
                close(s);
                vTaskDelay(4000 / portTICK_PERIOD_MS);
                continue;
            }
            ESP_LOGI(TAG, "... socket send success");

            struct timeval receiving_timeout;
            receiving_timeout.tv_sec = 5;
            receiving_timeout.tv_usec = 0;
            if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &receiving_timeout,
                           sizeof(receiving_timeout)) < 0)
            {
                ESP_LOGE(TAG, "... failed to set socket receiving timeout");
                close(s);
                vTaskDelay(4000 / portTICK_PERIOD_MS);
                continue;
            }
            ESP_LOGI(TAG, "... set socket receiving timeout success");

            /* Read HTTP response */
            do
            {
                bzero(recv_buf, sizeof(recv_buf));
                r = read(s, recv_buf, sizeof(recv_buf) - 1);
                for (int i = 0; i < r; i++)
                {
                    putchar(recv_buf[i]);
                }
            } while (r > 0);

            ESP_LOGI(TAG, "... done reading from socket. Last read return=%d errno=%d.", r, errno);
            close(s);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(example_connect());
    xTaskCreate(&http_get_task, "http_get_task", 4096, NULL, 5, NULL);
}
