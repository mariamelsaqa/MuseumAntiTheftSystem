# Museum Anti-theft System

## Submitted By

| Name | Github |
| :---: | :---: |
| Mariam Elsaqa | [mariamelsaqa](https://github.com/mariamelsaqa)
| Mariam Ali | [mariamramadan1](https://github.com/mariamramadan1)
| Mohamed Ali | [Mohamedakhalil](https://github.com/Mohamedakhalil)
| Kirolos Mikhail | [KirolosAssaad](https://github.com/KirolosAssaad)

## Github Repo
[https://github.com/mariamelsaqa/MuseumAntiTheftSystem](https://github.com/mariamelsaqa/MuseumAntiTheftSystem)

## The proposal 
The proposal is to create a system that can be used in museums to prevent theft of works of art. The system will be composed of a camera that will be responsible for capturing the images of a thief when change in the pressure of the floor is detected, which shall also trigger an alarm. Admins will be able to see the images captured by the camera in real time through a web application. To turn of the alarm the admin will have to enter the correct password through a numberpad.

## The initial design
    

## Identified Components
| Component | Image | Link |
| :---: | :---: | :---: |
|Nucleo STM32 board for the MCU|![stmm-removebg-preview](https://user-images.githubusercontent.com/66432580/235498240-d0b9f7ff-8f5e-4902-9673-d2206655ca1c.png) | [click here](https://store.fut-electronics.com/products/nucleo-l432kc-stm32-arm-cortex-processing-board?_pos=3&_sid=48ed8e505&_ss=r)|
|Force Sensitive Resistor Sensor|![unnamed (1)](https://user-images.githubusercontent.com/66432580/235498678-790a640d-87bb-4b89-8be8-7b13213f1b23.png)| [click here](https://store.fut-electronics.com/collections/force-pressure-flex-1/products/force-sensitive-resistor-square)|
|ESP32-Cam|![2-4-removebg-preview](https://user-images.githubusercontent.com/66432580/235498482-5766401c-70d7-4645-93e0-ec59ab4ba62f.png) | [click here](https://store.fut-electronics.com/collections/camera/products/esp32-cam-development-board-with-camera)|
|Buzzer|![buzzer-removebg-preview](https://user-images.githubusercontent.com/66432580/235498269-09e48796-bdba-410b-a129-3aeb8cc4b2e5.png)| [click here](https://store.fut-electronics.com/products/buzzer-3-v?_pos=2&_sid=4215a7f5f&_ss=r)|
|Keypad|![keypad-removebg-preview](https://user-images.githubusercontent.com/66432580/235498527-e2eb3870-e72a-4c74-b240-61768cda4a80.png) | [click here](https://store.fut-electronics.com/products/membrane-keypad-16-key-matrix-4x4?_pos=1&_sid=356c3914d&_ss=r)|
|LCD Display|![lcd-removebg-preview](<img width="266" alt="Screenshot_2023-05-29_at_2 34 41_AM-removebg-preview" src="https://github.com/mariamelsaqa/MuseumAntiTheftSystem/assets/64040952/175671ca-bce8-4a6f-b3d8-d7747a3407ed">)| [click here](https://www.alibaba.com/product-detail/1602-16x2-LCD-I2C-HD44780-Character_60516438236.html)|
|LEDs|![led-removebg-preview](https://user-images.githubusercontent.com/66432580/235498306-92520710-b18b-4a42-8361-eaa7795d7972.png) | [click here](https://store.fut-electronics.com/products/led-kit-5-colors-10-pieces?_pos=3&_sid=959c6e323&_ss=r)|

## Architecture
The following diagrams show the architecture of the system from both hardware and software perspectives.
### Block Diagram

![System Block Diagram](https://user-images.githubusercontent.com/70951947/235518679-4be1ae79-10cd-4b8b-9214-4ef2d2c9ad4d.jpeg)\
This diagram shows the main hardware components of our system and how they are integrated together. First and foremost, the STM32 Nucleo MCU is driven by a power supply to operate it remotely. It supplies the Vdd for the buzzer, LEDs, and the voltage divider circuit which will be discussed shortly. The buzzer and LEDs serve as our alarm system. This Alarm system can be controlled by the user via the keypad in order to authorize themselves. The voltage divider circuit is the one responsible for measuring changes that may happen to museum artifacts. The voltage is dropped across the resistor and force-sensitive resistor. As the weight of the artifact decreases, the resistance increases which decreases the voltage input at the Analog to Digital Converter pin at the STM.

### Flowchart
![Flowchart](https://user-images.githubusercontent.com/62829528/235503126-fd9825af-dace-4419-9d73-28d38619eaa8.jpg)\
This flowchart illustrates how different modules interact with each other on the software level. At the beginning, the main module will keep polling for the force sensor reading. If the reading decreases than a certain threshold, which means the artifact is being tampered with, then it will check for the authorization of the user. The user can authorize themselves through the attached keypad. If the password mismatches then there is a security breach in the system and the alarm will trigger. The alarm is composed of a buzzer, LED, and ESP32 Camera to identify the thief. Otherwise, then the access was authorized and the theft is eliminated.

## Timeline
1. Experiment with the sensor to determine the correct amount of resistance in the voltage divider circuit and start integrating it with the MCU ADC peripheral.
2. Integrating the alarm system as it is dependent on the FSR readings.
3. Integrating the keypad module with the system to allow for authorized access.
4. Setting up a web server and linking it to the ESP32 camera to be able to identify the user in case of a breach.

## First Update
We were able to get each component functional on its own, but we did not integrate them yet to have a fully functional system.
1. The pressure sensor can detect when the artifact is removed and it turns on the alarm and the LED
2. The ESP-32 camera is working and can take footage.
3. The keypad is fully functional using polling.

#### Demo for the pressure sensor, buzzer and LED


https://github.com/shalan/CSCE4301-WiKi/assets/66432580/85d5bdad-e7a9-40f8-aa40-45e075fa621b



#### Demo for the functional ESP-32 camera


https://github.com/shalan/CSCE4301-WiKi/assets/66432580/0193a06f-0b19-4477-b0f2-c12fc1b0b76d



#### Demo for the keypad

https://github.com/shalan/CSCE4301-WiKi/assets/64040952/f5dc4f0d-4087-4cec-902b-4667af6b2203

### Challenges 
The most challenging part was to get the ESP-32 camera functional as it was hard to interface the ESP-32 camera.

### TO-DO
1- Integrate the whole system.  
2- The camera should capture a photo and send it to a drive when the artifact is moved.  
3- The alarm should be turned off when the passcode is entered correctly.  
4- Test the system.  
