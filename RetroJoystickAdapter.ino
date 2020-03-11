/*
 * Link
 *  mcgurk/Arduino-USB-HID-RetroJoystickAdapter
 *  https://github.com/mcgurk/Arduino-USB-HID-RetroJoystickAdapter
 *  
 * Library
 *  dmadison/ArduinoXInput
 *  https://github.com/dmadison/ArduinoXInput
 */

/* 
 * SFC(SNES)はDataPinから16bitデータが飛んでくる。引用元:https://wiki.superfamicom.org/controllers#toc-3
 * bits: byetUDLRaxlr0000
 * b/y/a/x/l/r are the similarly named buttons. 'e' is select. 't' is start. 
 * U/D/L/R are the pad directions. 
 * 
 * N64はDataPinから32bitデータが飛んでくる　引用元http://www.mixdown.ca/n64dev/
 * line1 bits: A, B, Z, Start, Dup, Ddown, Dleft, Dright 
 * line2 bits: 0, 0, L, R, Cup, Cdown, Cleft, Cright
 * line3 bits: Stick_AxisX
 * line4 bits: Stick_AxisY
 * 入力の取得はそれぞれ取得方法が違うので別の.inoに記述
 * この辺は大体下記より ぶっちゃけN64の入力取得とか何やってるのかわからん
 * https://github.com/mcgurk/Arduino-USB-HID-RetroJoystickAdapter
 */
 
#include "XInput.h"
#include "pins_arduino.h"

//Connector (Connect also GND and 5V):    CLOCK, LATCH, DATA
const uint8_t inputPinsSNES[] =         {    5,    6,    7    };

//Connector (Connect also GND and 3.3V):  DATA
const uint8_t inputPinsN64[] =         {    2    };

const int ADC_Max =  127; //7bit

// 8 bytes of data that we get from the controller
struct {
    // bits: A, B, Z, Start, Dup, Ddown, Dleft, Dright
    unsigned char data1;
    // bits: 0, 0, L, R, Cup, Cdown, Cleft, Cright
    unsigned char data2;
    char stick_x;
    char stick_y;
} N64_status;
 
void setup(){
  setupSnesJoystick();  //SNES.inoに記述
  setupN64Joystick();   //N64.inoに記述
  
  XInput.setJoystickRange(0, ADC_Max);
  XInput.setAutoSend(false);  // Wait for all controls before sending
  XInput.begin();
}

void loop(){
//  unsigned char n64DataArr[4];
  
  uint16_t snesData = readSnesJoystick(); //SFCのコントローラから情報取得
  readN64Joystick();  //N64のコントローラから情報取得　構造体はN64.ino参照  戻り値で配列返す方法とか無いかな…

  int8_t n64Data[4];
  n64Data[0] = N64_status.data1;    //bits: A, B, Z, Start, Dup, Ddown, Dleft, Dright
  n64Data[1] = N64_status.data2;    //bits: 0, 0, L, R, Cup, Cdown, Cleft, Cright
  n64Data[2] = N64_status.stick_x;  //bits: stick_x
  n64Data[3] = N64_status.stick_y;  //bits: stick_y
                                                                //SNES : N64
  boolean buttonA = !bitRead(snesData,0) | (n64Data[0] & 128);  //B : A
  boolean buttonB = !bitRead(snesData,8) | (n64Data[1] & 4);    //A : Cdown
  boolean buttonX = !bitRead(snesData,9) | (n64Data[1] & 2);    //X : CLeft
  boolean buttonY = !bitRead(snesData,1) | (n64Data[0] & 64);   //Y : B

  boolean buttonLB = !bitRead(snesData,10) | (n64Data[1] & 32); //L : L
  boolean buttonRB = !bitRead(snesData,11) | (n64Data[1] & 16); //R : R

  boolean buttonBack  = !bitRead(snesData,2) | (n64Data[0] & 32); //Select : Z
  boolean buttonStart = !bitRead(snesData,3) | (n64Data[0] & 16); //Start : Start

  boolean buttonL3 = (n64Data[1] & 8);    //none : Cup
  boolean buttonR3 = (n64Data[1] & 1);    //none : Cright

  boolean dpadUp    = !bitRead(snesData,4) | (n64Data[0] & 8); //Up : UP
  boolean dpadDown  = !bitRead(snesData,5) | (n64Data[0] & 4); //Down : Down
  boolean dpadLeft  = !bitRead(snesData,6) | (n64Data[0] & 2); //Left : Left
  boolean dpadRight = !bitRead(snesData,7) | (n64Data[0] & 1); //Right : Right

  int leftJoyX = n64Data[2] + (ADC_Max / 2);  //N64_Stick_x
  int leftJoyY = n64Data[3] + (ADC_Max / 2);  //N64_Stick_y
  
  // Set XInput buttons
  XInput.setButton(BUTTON_A, buttonA);
  XInput.setButton(BUTTON_B, buttonB);
  XInput.setButton(BUTTON_X, buttonX);
  XInput.setButton(BUTTON_Y, buttonY);

  XInput.setButton(BUTTON_LB, buttonLB);
  XInput.setButton(BUTTON_RB, buttonRB);

  XInput.setButton(BUTTON_BACK, buttonBack);
  XInput.setButton(BUTTON_START, buttonStart);

  XInput.setButton(BUTTON_L3, buttonL3);
  XInput.setButton(BUTTON_R3, buttonR3);

  // Set XInput DPAD values
  XInput.setDpad(dpadUp, dpadDown, dpadLeft, dpadRight);

  // Set XInput LeftJoystick
  XInput.setJoystick(JOY_LEFT, leftJoyX, leftJoyY);

  XInput.send();
}
