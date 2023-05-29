# Running the nucleo STM L432KC board
## Description
This folder contains the code for the nucleo STM L432KC board.
## Requirements
- [Keil uVision5](https://developer.arm.com/documentation/101407/0538/About-uVision/Installation)
- [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html#get-software)
- [STM32L432KC nucleo board](https://store.fut-electronics.com/products/nucleo-l432kc-stm32-arm-cortex-processing-board?_pos=3&_sid=48ed8e505&_ss=r)

## Directories
- `STM_Source/Src`: Contains the source code for the nucleo STM L432KC board.
- `STM_Source/Inc`: Contains the header files for the nucleo STM L432KC board.

## How to run
- Open CubeMX and configure PA0-PA1-PA4-PA5 as GPIO_Input, configure PA6 till PA8, PA11, PA12 as GPIO_Output.
- generate the code and open the project in Keil uVision5.
- Connect the keypad, LCD, FSR, the buzzer, the LED and the camera to the nucleo board.
- Copy the code from `STM_Source/Src` and `STM_Source/Inc` to the newly generated project.
- Build the project and flash it to the board.
- In this phase, the board can be tested using all components other than the camera.
- The object to be put on the FSR should be a small object (around 10-20 grams).
- To test the camera, follow the instructions in `CAM_CODE/README.md` to run the camera code on the ESP32 board.