# RetroJoystickAdapter
SFC(SNES) and N64 Controller to XInput

Arduino Leonardoを使用し、SFC(SNES)とN64のコントローラをXInputとして認識させます。  
SFC,N64のコントローラを両方接続しても1つのデバイスとして認識されます。(SFCのAボタンとN64のAボタンは同じ入力として処理)
  
SFCコンはCLOCK=5pin, LATCH=6pin、DATA=7pinへ接続、
N64コンはDATA=2pinへ接続するようにしています。
SFC(SNES)は5v、N64は3.3vで動作するようなので注意
  
Steamで買った2Dゲームとかが快適に遊べるようになったので満足
  
Link
-
 mcgurk/Arduino-USB-HID-RetroJoystickAdapter
 https://github.com/mcgurk/Arduino-USB-HID-RetroJoystickAdapter
 
Library
-
 dmadison/ArduinoXInput
 https://github.com/dmadison/ArduinoXInput
