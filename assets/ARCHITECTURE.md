# Architecture
The following diagrams show the architecture of the system from both hardware and software perspectives.
## Block Diagram

![WhatsApp Image 2023-05-29 at 8 11 51 AM](https://github.com/mariamelsaqa/MuseumAntiTheftSystem/assets/64040952/554a0dc9-71ea-41ee-b1d4-05fce0c62bc2)

This diagram shows the main hardware components of our system and how they are integrated together. The buzzer and LEDs serve as our alarm system. This Alarm system can be controlled by the user via the keypad in order to authorize themselves. The voltage divider circuit is the one responsible for measuring changes that may happen to museum artifacts. The voltage is dropped across the resistor and force-sensitive resistor. As the weight of the artifact decreases, the resistance increases which decreases the voltage input at the Analog to Digital Converter pin at the STM.

## Flowchart
![Flowchart](https://user-images.githubusercontent.com/62829528/235503126-fd9825af-dace-4419-9d73-28d38619eaa8.jpg)\
This flowchart illustrates how different modules interact with each other on the software level. At the beginning, the main module will keep polling for the force sensor reading. If the reading decreases than a certain threshold, which means the artifact is being tampered with, then it will check for the authorization of the user. The user can authorize themselves through the attached keypad. If the password mismatches then there is a security breach in the system and the alarm will trigger. The alarm is composed of a buzzer, LED, and ESP32 Camera to identify the thief. Otherwise, then the access was authorized and the theft is eliminated.
