# CAMERA CODES

## PRE-REQUISITES
ALL DEVICES MUST BE CONNECT TO THE SAME WIFI NETWORK
## Description
This folder contains all the codes needed to capture the image from the camera and send it to the server upon input change.

## Requirements
- [ESP-IDF v4.0 or above](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)
- [LILYGO TTGO T-Camera ESP32 WROVER with PSRAM](http://www.lilygo.cn/prod_view.aspx?TypeId=50067&Id=1273&FId=t3:50067:3)
- [ESP32](https://www.tme.eu/eg/en/details/esp32-devkitc-s1/development-kits-for-data-transmission/espressif/)
- [Node](https://nodejs.org/en/download/) 
- [npm](https://www.npmjs.com/get-npm) 

## Directories 
- `backendServer`: Contains the code for the backend server that would run on a PC.
- `ESP32`: Contains the code for the ESP32 board to caall the backendServer APIs.
- `LILYGO`: Contains the code for the LILYGO TTGO T-Camera ESP32 WROVER with PSRAM board to setup an HTTP server and send the image to the backendServer.

## How to run


### LILYGO
- Open the LILYGO folder and go to the [connect_wifi.c](./LILYGO/main/connect_wifi.c) file.
- Change the `WIFI_SSID` and `WIFI_PASS` to your WiFi SSID and password.
- Run `idf.py build flash monitor` to build the code, flash it to the board and monitor the output.
- The board will connect to the WiFi and start an HTTP server on port 80.
- Copy the ip address of the board from the output and paste it in the [backendServer/index.js](./backendServer/index.js) file in the API request.


### backendServer
- Open the backendServer folder and run `npm install` to install all the dependencies.
- Change the IP address to your PC's IP address using command `ipconfig` in the command prompt. or `ifconfig` in the terminal for linux.
- Use `npm start` to run the server, or `npm run dev` to run the server in development mode.
- The server will run on port 3000 by default.


### ESP32
- Open the ESP32 folder and run `idf.py menuconfig` to configure the board.
- Go to `Example Configuration` and change the `WiFi SSID` and `WiFi Password` to your WiFi SSID and password.
- Change the `Server IP` to your PC's IP address.
- Change the `Server Port` to the port you are running the server on. (3000 by default)
- Run `idf.py build flash monitor` to build the code, flash it to the board and monitor the output.
- The board will connect to the WiFi and send a request to the server every time the input at pin D4 changes.
