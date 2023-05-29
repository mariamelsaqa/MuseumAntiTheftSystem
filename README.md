# Museum Anti-theft System

## Authors:

| Name | Github |
| :---: | :---: |
| Mariam Elsaqa | [mariamelsaqa](https://github.com/mariamelsaqa)
| Mariam Ali | [mariamramadan1](https://github.com/mariamramadan1)
| Mohamed Ali | [Mohamedakhalil](https://github.com/Mohamedakhalil)
| Kirolos Mikhail | [KirolosAssaad](https://github.com/KirolosAssaad)

## What is this project?
The proposal is to create a system that can be used in museums to prevent theft of works of art. The system will be composed of a camera that will be responsible for capturing the images of a thief when change in the pressure of the floor is detected, which shall also trigger an alarm. Admins will be able to see the images captured by the camera in real time through a web application. To turn of the alarm the admin will have to enter the correct password through a numberpad.

## Project Design
    

## Identified Components
| Component | Image |
| :---: | :---: |
|[Nucleo STM32 board for the MCU](https://store.fut-electronics.com/products/nucleo-l432kc-stm32-arm-cortex-processing-board?_pos=3&_sid=48ed8e505&_ss=r)|![stmm-removebg-preview](https://user-images.githubusercontent.com/66432580/235498240-d0b9f7ff-8f5e-4902-9673-d2206655ca1c.png)|
|[Force Sensitive Resistor Sensor](https://store.fut-electronics.com/collections/force-pressure-flex-1/products/force-sensitive-resistor-square)|![unnamed (1)](https://user-images.githubusercontent.com/66432580/235498678-790a640d-87bb-4b89-8be8-7b13213f1b23.png)|
|[LILLYGO CAM](http://www.lilygo.cn/prod_view.aspx?TypeId=50067&Id=1273&FId=t3:50067:3)|<img width="285" alt="LILLYGO" src="https://github.com/mariamelsaqa/MuseumAntiTheftSystem/assets/66432580/79843fce-5966-4a3f-b423-33f4d2ec7b8b">|
|[ESP32](https://www.tme.eu/eg/en/details/esp32-devkitc-s1/development-kits-for-data-transmission/espressif/?brutto=1&currency=USD&gclid=Cj0KCQjw98ujBhCgARIsAD7QeAjpbOXTiMhu-4_GcjQN9xVIJMIN7XYYynX8KB4FPCby52vo_oHhkb0aAqGyEALw_wcB)|<img width="285" alt="Screenshot_2023-05-29_at_3 43 57_AM-removebg-preview" src="https://github.com/shalan/CSCE4301-WiKi/assets/64040952/4869950b-2738-4eb0-b3ee-43d2adb2377d">|
|[Buzzer](https://store.fut-electronics.com/products/buzzer-3-v?_pos=2&_sid=4215a7f5f&_ss=r)|![buzzer-removebg-preview](https://user-images.githubusercontent.com/66432580/235498269-09e48796-bdba-410b-a129-3aeb8cc4b2e5.png)|
|[Keypad](https://store.fut-electronics.com/products/membrane-keypad-16-key-matrix-4x4?_pos=1&_sid=356c3914d&_ss=r)|![keypad-removebg-preview](https://user-images.githubusercontent.com/66432580/235498527-e2eb3870-e72a-4c74-b240-61768cda4a80.png)|
|[LCD Display with serial interface adapter module](https://www.alibaba.com/product-detail/1602-16x2-LCD-I2C-HD44780-Character_60516438236.html)|<img width="266" alt="Screenshot_2023-05-29_at_2 34 41_AM-removebg-preview" src="https://github.com/shalan/CSCE4301-WiKi/assets/64040952/dd12448f-f3ff-47f7-9086-4b936da354bc">|
|[LEDs](https://store.fut-electronics.com/products/led-kit-5-colors-10-pieces?_pos=3&_sid=959c6e323&_ss=r)|![led-removebg-preview](https://user-images.githubusercontent.com/66432580/235498306-92520710-b18b-4a42-8361-eaa7795d7972.png) |

## Architecture
The following diagrams show the architecture of the system from both hardware and software perspectives.
### Block Diagram

![WhatsApp Image 2023-05-29 at 8 11 51 AM](https://github.com/mariamelsaqa/MuseumAntiTheftSystem/assets/64040952/554a0dc9-71ea-41ee-b1d4-05fce0c62bc2)

This diagram shows the main hardware components of our system and how they are integrated together. The buzzer and LEDs serve as our alarm system. This Alarm system can be controlled by the user via the keypad in order to authorize themselves. The voltage divider circuit is the one responsible for measuring changes that may happen to museum artifacts. The voltage is dropped across the resistor and force-sensitive resistor. As the weight of the artifact decreases, the resistance increases which decreases the voltage input at the Analog to Digital Converter pin at the STM.

### Flowchart
![Flowchart](https://user-images.githubusercontent.com/62829528/235503126-fd9825af-dace-4419-9d73-28d38619eaa8.jpg)\
This flowchart illustrates how different modules interact with each other on the software level. At the beginning, the main module will keep polling for the force sensor reading. If the reading decreases than a certain threshold, which means the artifact is being tampered with, then it will check for the authorization of the user. The user can authorize themselves through the attached keypad. If the password mismatches then there is a security breach in the system and the alarm will trigger. The alarm is composed of a buzzer, LED, and ESP32 Camera to identify the thief. Otherwise, then the access was authorized and the theft is eliminated.


### Our Final Connections
<img width="1139" alt="Screenshot 2023-05-29 at 9 11 08 AM" src="https://github.com/mariamelsaqa/MuseumAntiTheftSystem/assets/64040952/c20c578c-f680-4935-a315-d79d046993aa">


- We connect the buzzer and LED with the same GPIO_Output pin.   
- We connect the upper pins of the keypads with 4 GPIO_Output pins, GND, 3v3 respectively.  
- We connect the lower pins of the keypads with 4 GPIO_Input pins, GND, 3v3 respectively.  
- We connect the LCD with I2C SCL and SDA.  
- We connect the FSR with ADC (add 100k resistance) and GND.
- We connect the ESP with Ground and GPIO_Output.



## How to Replicate
### To initially integrate the system:  
- we had to trigger the buzzer and LED by interrupts not polling.  
### To get the ESP-32 CAM work:  
- We configured LILLYGO as a server that only works when it gets called to send a picture.
- The host laptop works as a server that contains a GET Request that requests the picture from LILLYGO server. 
- ESP-32 receives a trigger from STM (the same as the one received by the buzzer and LED) to call the host laptop API.

## How to Deploy
### prerequisites
- Keil V5
- CubeMX
- ESP-IDF
- NPM
- Node JS & Express JS

### Steps 
- Open CubeMX and configure PA0-PA1-PA4-PA5 as GPIO_Input, configure PA6 till PA8, PA11, PA12 as GPIO_Output.
- Configure UART2, ADC1, I2C1.
- Clone the repo and copy the main.c, stm_it to your project.
- Add liquid crystal .c and header files to your project.
- In the LILLYGO directory run this command: ```idf.py build flash monitor```
- In the ESP-32 directory run this command: ```idf.py build flash monitor```
- In the backend server directory run this command: ```npm run dev```

## Future work
- deploy the server on the cloud.
- create a 3D case for the whole system.
- Add face detection using tiny machine learning.
