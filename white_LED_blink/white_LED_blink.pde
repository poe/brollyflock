#define clockpin 13 // CI
#define enablepin 10 // EI
#define latchpin 9 // LI
#define datapin 11 // DI

#define NumLEDs 8

int LEDChannels[NumLEDs][3] = {0};
int SB_CommandMode;
int SB_RedCommand;
int SB_GreenCommand;
int SB_BlueCommand;

void setup() {

  pinMode(datapin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pinMode(enablepin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(0<<SPR0);
  digitalWrite(latchpin, LOW);
  digitalWrite(enablepin, LOW);


}

void SB_SendPacket() {

  if (SB_CommandMode == B01) {
    SB_RedCommand = 120;
    SB_GreenCommand = 100;
    SB_BlueCommand = 100;
  }

  SPDR = SB_CommandMode << 6 | SB_BlueCommand>>4;
  while(!(SPSR & (1<<SPIF)));
  SPDR = SB_BlueCommand<<4 | SB_RedCommand>>6;
  while(!(SPSR & (1<<SPIF)));
  SPDR = SB_RedCommand << 2 | SB_GreenCommand>>8;
  while(!(SPSR & (1<<SPIF)));
  SPDR = SB_GreenCommand;
  while(!(SPSR & (1<<SPIF)));

}

void WriteLEDArray() {

  SB_CommandMode = B00; // Write to PWM control registers
  for (int h = 0;h<NumLEDs;h++) {
    SB_RedCommand = LEDChannels[h][0];
    SB_GreenCommand = LEDChannels[h][1];
    SB_BlueCommand = LEDChannels[h][2];
    SB_SendPacket();
  }

  delayMicroseconds(15);
  digitalWrite(latchpin,HIGH); // latch data into registers
  delayMicroseconds(15);
  digitalWrite(latchpin,LOW);

  SB_CommandMode = B01; // Write to current control registers
  for (int z = 0; z < NumLEDs; z++) SB_SendPacket();
  delayMicroseconds(15);
  digitalWrite(latchpin,HIGH); // latch data into registers
  delayMicroseconds(15);
  digitalWrite(latchpin,LOW);

}

void loop() {

  for(int i = 0;i <NumLEDs;i++){
    LEDChannels[i][0] = 1023;
    LEDChannels[i][1] = 1023;
    LEDChannels[i][2] = 1023;
  }

  WriteLEDArray();
  delay(2000);

  for(int i = 0;i <NumLEDs;i++){
    LEDChannels[i][0] = 0;
    LEDChannels[i][1] = 0;
    LEDChannels[i][2] = 0;
  }

  WriteLEDArray();
  delay(1000);
}

