# RetroJoystickAdapter
SFC(SNES) and N64 Controller to XInput

Arduino Leonardoを使用し、SFC(SNES)とN64のコントローラをまとめて1つのXInputコントローラとして認識させます。  
  
```
SFC(SNES)
    VDD   = +5v
    CLOCK = 5pin
    LATCH = 6pin
    DATA  = 7pin

N64
    VDD   = +3.3v
    DATA  = 2pin
```
  
Requirements
-
Library  
 (dmadison/ArduinoXInput) &nbsp; https://github.com/dmadison/ArduinoXInput  
  
Board Package  
(dmadison/ArduinoXInput_AVR) &nbsp; https://github.com/dmadison/ArduinoXInput_AVR
  
Link
-
(mcgurk/Arduino-USB-HID-RetroJoystickAdapter) &nbsp; https://github.com/mcgurk/Arduino-USB-HID-RetroJoystickAdapter

License
-
https://github.com/hakonoko/RetroJoystickAdapter/blob/master/LICENSE
