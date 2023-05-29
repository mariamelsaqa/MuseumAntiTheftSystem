# Museum Anti-theft System
## WIKI PAGE
[https://github.com/shalan/CSCE4301-WiKi/wiki/G1:-Museum-Anti-theft-System](https://github.com/shalan/CSCE4301-WiKi/wiki/G1:-Museum-Anti-theft-System)
## Authors:

| Name | Github |
| :---: | :---: |
| Mariam Elsaqa | [mariamelsaqa](https://github.com/mariamelsaqa)
| Mariam Ali | [mariamramadan1](https://github.com/mariamramadan1)
| Mohamed Ali | [Mohamedakhalil](https://github.com/Mohamedakhalil)
| Kirolos Mikhail | [KirolosAssaad](https://github.com/KirolosAssaad)

## Main Assets
- [components](./assets/COMPONENTS.md)
- [Architecture](./assets/ARCHITECTURE.md)
- [connections](./assets/CONNECTIONS.md)


## Installation
- Download [Kiel V5](https://developer.arm.com/documentation/101407/0538/About-uVision/Installation) and [CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html#get-software) for the nucleo STM L432KC configurations.
- Download [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/) for the ESP-32 configurations and the LILLYGO cam configurations.
- To develop using ESP-IDF, VSCode is recommeneded. Download [VSCode](https://code.visualstudio.com/download) and install the [ESP-IDF extension](https://marketplace.visualstudio.com/items?itemName=espressif.esp-idf-extension).
- To run the backend server, download [Node JS](https://nodejs.org/en/download/) and [NPM](https://www.npmjs.com/get-npm).

## How to run
- To run the nucleo STM L432KC, follow the STM_Source [README.md](./STM_Source/README.md) file.
- To run the ESP-32, LILYGO or the backend server, follow the CAM_CODE [README.md](./CAM_CODE/README.md) file.


## File Structure
Our repos consists of 2 directories: 
1- STM Source Code: 

It contains the C and header files that should be copied into your keil project.

2- ESP-32 CAM Code: 
- `backendServer`: Contains the code for the backend server that would run on a PC.
- `ESP32`: Contains the code for the ESP32 board to caall the backendServer APIs.
- `LILYGO`: Contains the code for the LILYGO TTGO T-Camera ESP32 WROVER with PSRAM board to setup an HTTP server and send the image to the backendServer.  


## References
- [LCD tutorial](https://www.youtube.com/watch?v=EYrHRSeAUUc&t=363s)  
- [ESP IDF repo](https://github.com/espressif/esp-idf)
- [Keypad Datasheet](https://digilent.com/reference/_media/pmod:pmod:pmodKYPD_rm.pdf)
- [Keypad tutorial](https://controllerstech.com/use-4x4-keypad-with-stm32/)
