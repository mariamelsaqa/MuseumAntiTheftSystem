# Final Connections
<img width="1139" alt="Screenshot 2023-05-29 at 9 11 08 AM" src="https://github.com/mariamelsaqa/MuseumAntiTheftSystem/assets/64040952/c20c578c-f680-4935-a315-d79d046993aa">


- We connect the buzzer and LED with the same GPIO_Output pin.   
- We connect the upper pins of the keypads with 4 GPIO_Output pins, GND, 3v3 respectively.  
- We connect the lower pins of the keypads with 4 GPIO_Input pins, GND, 3v3 respectively.  
- We connect the LCD with I2C SCL and SDA.  
- We connect the FSR with ADC (add 100k resistance) and GND.
- We connect the ESP with Ground and GPIO_Output.
