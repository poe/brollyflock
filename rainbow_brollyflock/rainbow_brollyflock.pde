#define clockpin 13 // CI
#define enablepin 10 // EI
#define latchpin 9 // LI
#define datapin 11 // DI
 
#define NumLEDs 3
 
#define REDPIN 3
#define GREENPIN 6
#define BLUEPIN 5
 
#define FADESPEED 5     // make this higher to slow down
 
int LEDChannels[NumLEDs][3] = {0};
int SB_CommandMode;
int SB_RedCommand;
int SB_GreenCommand;
int SB_BlueCommand;
 
void setup() {
  
   Serial.begin(9600);           // set up Serial library at 9600 bps
  
   Serial.println("Hello rainbow!");  // prints hello with ending line break 


   pinMode(REDPIN, OUTPUT);
   pinMode(GREENPIN, OUTPUT);
   pinMode(BLUEPIN, OUTPUT);

  
   for(int i = 0; i< 14; i++){
     pinMode(i,OUTPUT);
     digitalWrite(i,LOW);
   }

 
  
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
 
int red = 255;
int green = 0;
int blue = 0;
 
int i =0;
 
void loop() {   

   if(i > 768){
     i = 0;
   }
   
   i++;
   
   if(i < 256){
     green = 0;
     red--;
     blue++;
   }
   if(i > 256 && i < 512){
     red = 0;
     blue--;
     green++;
   }
   if(i > 512){
     blue = 0;
     green--;
     red++;
   }
   
   
   LEDChannels[0][0] = red;
   LEDChannels[0][1] = green;
   LEDChannels[0][2] = blue;
 
   LEDChannels[1][0] = red;
   LEDChannels[1][1] = green;
   LEDChannels[1][2] = blue;

   LEDChannels[2][0] = red;
   LEDChannels[2][1] = green;
   LEDChannels[2][2] = blue;

   WriteLEDArray();

   int val; 
   val = red;
   val = map(val, 0, 1023, 0, 255);
   analogWrite(REDPIN, val);

   val = green;
   val = map(val, 0, 1023, 0, 255);
   analogWrite(GREENPIN, val);

   val = blue;
   val = map(val, 0, 1023, 0, 255);
   analogWrite(BLUEPIN, val);

   Serial.print("red = ");   
   Serial.print(red);
   Serial.print("green = ");   
   Serial.print(green);
   Serial.print("blue = ");   
   Serial.print(blue);
   Serial.println(" ");

   delayMicroseconds(analogRead(3));
   delayMicroseconds(analogRead(4));
   delayMicroseconds(analogRead(5));
}
