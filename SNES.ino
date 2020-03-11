/*
 * SFC(SNES)関係の処理抜き出し
 */

#define SNES_CLOCK inputPinsSNES[0]
#define SNES_LATCH inputPinsSNES[1]
#define SNES_DATA inputPinsSNES[2]

void setupSnesJoystick(){
  pinMode(SNES_CLOCK, OUTPUT);
  pinMode(SNES_LATCH, OUTPUT);
  pinMode(SNES_DATA, INPUT_PULLUP);
}

uint16_t readSnesJoystick(){
  uint16_t snesDataTmp;
  
  digitalWrite(SNES_LATCH, LOW);
  digitalWrite(SNES_CLOCK, LOW);
  digitalWrite(SNES_LATCH, HIGH);
  delayMicroseconds(12);
  digitalWrite(SNES_LATCH, LOW);
 
  for (int i = 0; i < 16; i++)  //SFC(SNES)はコントローラの信号が16bitなので
  {
     bitWrite(snesDataTmp, i, digitalRead(SNES_DATA));
     digitalWrite(SNES_CLOCK, HIGH);
     delayMicroseconds(12);
     digitalWrite(SNES_CLOCK, LOW);
     delayMicroseconds(12);
  }
  return snesDataTmp;
}
