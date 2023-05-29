# CAMERA CODES

## Description
This folder contains all the codes needed to capture the image from the camera and send it to the server upon input change.

## Requirements
- ESP-IDF v4.0 or above
- LILYGO TTGO T-Camera ESP32 WROVER with PSRAM
- ESP32

## Directories 
- `backendServer`: Contains the code for the backend server that would run on a PC.
- `ESP32`: Contains the code for the ESP32 board to caall the backendServer APIs.
- `LILYGO`: Contains the code for the LILYGO TTGO T-Camera ESP32 WROVER with PSRAM board to setup an HTTP server and send the image to the backendServer.