
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2023 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_hal.h"

/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "liquidcrystal_i2c.h.txt"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim16;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t alarm=0, access=0;
int count = 0;
char arr[20];
char pass[] = "1234";

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_RTC_Init(void);
static void MX_I2C1_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM16_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
static void keypad(void);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
#define C4_GPIO_PIN GPIO_PIN_7
#define C3_GPIO_PIN GPIO_PIN_6
#define C2_GPIO_PIN GPIO_PIN_8
#define C1_GPIO_PIN GPIO_PIN_11

#define R4_GPIO_PIN GPIO_PIN_0
#define R3_GPIO_PIN GPIO_PIN_1
#define R2_GPIO_PIN GPIO_PIN_5
#define R1_GPIO_PIN GPIO_PIN_4

uint8_t x;

void keypad(void){
			HAL_GPIO_WritePin (GPIOA, C1_GPIO_PIN, GPIO_PIN_RESET);	//Pull the C1 low
		HAL_GPIO_WritePin (GPIOA, C2_GPIO_PIN, GPIO_PIN_SET);  // Pull the C2 High
		HAL_GPIO_WritePin (GPIOA, C3_GPIO_PIN, GPIO_PIN_SET);  // Pull the C3 High
		HAL_GPIO_WritePin (GPIOA, C4_GPIO_PIN, GPIO_PIN_SET);  // Pull the C4 High

		if (!(HAL_GPIO_ReadPin (GPIOA, R1_GPIO_PIN)))   // if the Col 1 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R1_GPIO_PIN)));   // wait till the button is pressed
			x = '1';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}

		if (!(HAL_GPIO_ReadPin (GPIOA, R2_GPIO_PIN)))   // if the Col 2 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R2_GPIO_PIN)));   // wait till the button is pressed
			x = '4';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}

		if (!(HAL_GPIO_ReadPin (GPIOA, R3_GPIO_PIN)))   // if the Col 3 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R3_GPIO_PIN)));   // wait till the button is pressed
			x = '7';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}

		if (!(HAL_GPIO_ReadPin (GPIOA, R4_GPIO_PIN)))   // if the Col 4 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R4_GPIO_PIN)));   // wait till the button is pressed
			x = '0';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}
		
		
		HAL_GPIO_WritePin (GPIOA, C1_GPIO_PIN, GPIO_PIN_SET);	//Pull the C1 high
		HAL_GPIO_WritePin (GPIOA, C2_GPIO_PIN, GPIO_PIN_RESET);  // Pull the C2 low
		HAL_GPIO_WritePin (GPIOA, C3_GPIO_PIN, GPIO_PIN_SET);  // Pull the C3 High
		HAL_GPIO_WritePin (GPIOA, C4_GPIO_PIN, GPIO_PIN_SET);  // Pull the C4 High

		if (!(HAL_GPIO_ReadPin (GPIOA, R1_GPIO_PIN)))   // if the Col 1 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R1_GPIO_PIN)));   // wait till the button is pressed
			x = '2';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}

		if (!(HAL_GPIO_ReadPin (GPIOA, R2_GPIO_PIN)))   // if the Col 2 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R2_GPIO_PIN)));   // wait till the button is pressed
			x = '5';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}

		if (!(HAL_GPIO_ReadPin (GPIOA, R3_GPIO_PIN)))   // if the Col 3 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R3_GPIO_PIN)));   // wait till the button is pressed
			x = '8';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}

		if (!(HAL_GPIO_ReadPin (GPIOA, R4_GPIO_PIN)))   // if the Col 4 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R4_GPIO_PIN)));   // wait till the button is pressed
			x = 'F';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}
		
		HAL_GPIO_WritePin (GPIOA, C1_GPIO_PIN, GPIO_PIN_SET);	//Pull the C1 high
		HAL_GPIO_WritePin (GPIOA, C2_GPIO_PIN, GPIO_PIN_SET);  // Pull the C2 high
		HAL_GPIO_WritePin (GPIOA, C3_GPIO_PIN, GPIO_PIN_RESET);  // Pull the C3 low
		HAL_GPIO_WritePin (GPIOA, C4_GPIO_PIN, GPIO_PIN_SET);  // Pull the C4 High

		if (!(HAL_GPIO_ReadPin (GPIOA, R1_GPIO_PIN)))   // if the Col 1 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R1_GPIO_PIN)));   // wait till the button is pressed
			x = '3';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}

		if (!(HAL_GPIO_ReadPin (GPIOA, R2_GPIO_PIN)))   // if the Col 2 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R2_GPIO_PIN)));   // wait till the button is pressed
			x = '6';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}

		if (!(HAL_GPIO_ReadPin (GPIOA, R3_GPIO_PIN)))   // if the Col 3 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R3_GPIO_PIN)));   // wait till the button is pressed
			x = '9';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}

		if (!(HAL_GPIO_ReadPin (GPIOA, R4_GPIO_PIN)))   // if the Col 4 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R4_GPIO_PIN)));   // wait till the button is pressed
			x = 'E';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}
		
		HAL_GPIO_WritePin (GPIOA, C1_GPIO_PIN, GPIO_PIN_SET);	//Pull the C1 high
		HAL_GPIO_WritePin (GPIOA, C2_GPIO_PIN, GPIO_PIN_SET);  // Pull the C2 high
		HAL_GPIO_WritePin (GPIOA, C3_GPIO_PIN, GPIO_PIN_SET);  // Pull the C3 High
		HAL_GPIO_WritePin (GPIOA, C4_GPIO_PIN, GPIO_PIN_RESET);  // Pull the C4 low

		if (!(HAL_GPIO_ReadPin (GPIOA, R1_GPIO_PIN)))   // if the Col 1 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R1_GPIO_PIN)));   // wait till the button is pressed
			x = 'A';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}

		if (!(HAL_GPIO_ReadPin (GPIOA, R2_GPIO_PIN)))   // if the Col 2 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R2_GPIO_PIN)));   // wait till the button is pressed
			x = 'B';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}

		if (!(HAL_GPIO_ReadPin (GPIOA, R3_GPIO_PIN)))   // if the Col 3 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R3_GPIO_PIN)));   // wait till the button is pressed
			x = 'C';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}

		if (!(HAL_GPIO_ReadPin (GPIOA, R4_GPIO_PIN)))   // if the Col 4 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R4_GPIO_PIN)));   // wait till the button is pressed
			x = 'D';
			sprintf(&arr[count], "%c", x );
			count++;
			HAL_UART_Transmit(&huart2,&x , 1, 1000);
			HAL_Delay(250);
		}
		
		if (count <=4){
			
			HD44780_SetCursor(0,1);
			HD44780_PrintStr(arr);
			
			if(count == 4){
			if(strcmp(arr,pass) == 0){
				access = 1;
				HD44780_Clear();
				HD44780_SetCursor(0,0);
			HD44780_PrintStr("Access");
				HD44780_SetCursor(8,1);
			HD44780_PrintStr("Granted");
			}
			else 
				access = 0;
			}
		}
		else {
			for (int i =0; i<count; i++)
				arr[i] = ' ';
			count = 0;
			HD44780_Clear();
			sprintf(&arr[count], "%c", x );
			count++;
		}

		  
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    uint16_t AD_RES = 0, Vamb, DC_Multiplier, res;
	char msg[] = "\r\n Alarm ";
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_RTC_Init();
  MX_I2C1_Init();
  MX_ADC1_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */
// __HAL_RTC_ALARM_ENABLE_IT(&hrtc,RTC_IT_ALRA);
  HD44780_Init(2);
  HD44780_Clear();
//  HD44780_SetCursor(0,0);
//  HD44780_PrintStr("Password?");
//  HD44780_SetCursor(10,1);
//  HD44780_PrintStr("WORLD");
//  HAL_Delay(2000);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	   HAL_ADCEx_Calibration_Start(&hadc1,ADC_SINGLE_ENDED);
	HAL_TIM_Base_Start_IT(&htim16);
	HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 1);
    Vamb = HAL_ADC_GetValue(&hadc1);
		
    DC_Multiplier = 65535/(4096-Vamb);
  while (1)
  {
    

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
			HAL_ADC_Start(&hadc1);
       // Poll ADC1 Perihperal & TimeOut = 1mSec
        HAL_ADC_PollForConversion(&hadc1, 1);
       // Read The ADC Conversion Result & Map It To PWM DutyCycle
        AD_RES = HAL_ADC_GetValue(&hadc1);
				res = (AD_RES-Vamb)*DC_Multiplier;
//				HAL_UART_Transmit(&huart2, (uint8_t *)msg,sizeof(msg),1000);
		char arr[5] = {0, 0, 0, 0, 0};
		keypad();
		if(res<500){
			alarm=1;  
		}
		else {alarm = 0;}
		
		sprintf(arr, "%d\n", alarm);

//				HAL_UART_Transmit(&huart2, (uint8_t *)&arr,sizeof(5),1000);
//				HAL_UART_Transmit(&huart2, &alarm,1,1000);
		HAL_Delay(100);
		
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		
		
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure LSE Drive Capability
    */
  HAL_PWR_EnableBkUpAccess();

  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_LSE
                              |RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 36;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_ADC;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 16;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the main internal regulator output voltage
    */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /**Enable MSI Auto calibration
    */
  HAL_RCCEx_EnableMSIPLLMode();

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC1 init function */
static void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Common config
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel
    */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* I2C1 init function */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10808DD3;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Analogue filter
    */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Digital filter
    */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* RTC init function */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;
  RTC_AlarmTypeDef sAlarm;

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

    /**Initialize RTC Only
    */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initialize RTC and set the Time and Date
    */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Enable the Alarm A
    */
  sAlarm.AlarmTime.Hours = 0x0;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x10;
  sAlarm.AlarmTime.SubSeconds = 0x0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY|RTC_ALARMMASK_HOURS
                              |RTC_ALARMMASK_MINUTES;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 0x1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM16 init function */
static void MX_TIM16_Init(void)
{

  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 7199;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 4999;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_11
                          |GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA4 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA6 PA7 PA8 PA11
                           PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_11
                          |GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) { 
//  RTC_AlarmTypeDef sAlarm;
//  HAL_RTC_GetAlarm(hrtc,&sAlarm,RTC_ALARM_A,FORMAT_BIN);
//  if(sAlarm.AlarmTime.Seconds>58) {
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_RESET);
//    sAlarm.AlarmTime.Seconds=0;
//  }else{
//    sAlarm.AlarmTime.Seconds=sAlarm.AlarmTime.Seconds+1;
//  }
//    while(HAL_RTC_SetAlarm_IT(hrtc, &sAlarm, FORMAT_BIN)!=HAL_OK){}
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_SET);
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
