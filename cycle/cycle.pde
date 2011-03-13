#define datapin 11 // DI
#define latchpin 9 // LI
#define enablepin 10 // EI
#define clockpin 13 // CI

#define redpin 2
#define greenpin 3
#define bluepin 4

#define NumLEDs 10
#define MaxBright 1023
#define MinBright 0
 
int LEDChannels[NumLEDs][3] = {0};
int SB_CommandMode;
int SB_RedCommand;
int SB_GreenCommand;
int SB_BlueCommand;
int brightness;
int increase;
int redButton= 1;
int greenButton= 1;
int blueButton= 1;

int peak = 0;
int value = 0;
int level = 0;


void setup() {
 
   brightness = MinBright;
   increase = 1;
   
   pinMode(datapin, OUTPUT);
   pinMode(latchpin, OUTPUT);
   pinMode(enablepin, OUTPUT);
   pinMode(clockpin, OUTPUT);
   SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(0<<SPR0);
   digitalWrite(latchpin, LOW);
   digitalWrite(enablepin, LOW);
 
   pinMode(redpin, INPUT);
   pinMode(greenpin, INPUT);
   pinMode(bluepin, INPUT);
   
   digitalWrite(redpin, HIGH);
   digitalWrite(greenpin, HIGH);
   digitalWrite(bluepin, HIGH);
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
    delayMicroseconds(50);
    digitalWrite(latchpin,HIGH); // latch data into registers
    delayMicroseconds(50);
    digitalWrite(latchpin,LOW);
 
}

void loop() {
   
   brightness+=increase;
   
   redButton= digitalRead(redpin);
   greenButton= digitalRead(greenpin);
   blueButton= digitalRead(bluepin);
   
   if (brightness >= MaxBright * NumLEDs) {
     increase = -1;
   }
   
   else if (brightness <= MinBright) {
     increase = 1;
   }
   
   for(int i=0;i<NumLEDs;i++){
     value = brightness - (i * MaxBright);
     if (value  > MaxBright){
       level = MaxBright; 
     }
     else if (value < MinBright){
       level = MinBright;
     }
     else {
       level = value;
     }
     LEDChannels[i][0] = level * redButton;
     LEDChannels[i][1] = level * greenButton;
     LEDChannels[i][2] = level * blueButton;
   }
 
   WriteLEDArray();
//   delay(1);
 
}
