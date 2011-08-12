#include <avr/pgmspace.h> 


#define clockpin 13 // CI
#define enablepin 10 // EI
#define latchpin 9 // LI
#define datapin 11 // DI
 
#define NumLEDs 48

int LEDChannels[NumLEDs][3] = {0};
int SB_CommandMode;
int SB_RedCommand;
int SB_GreenCommand;
int SB_BlueCommand;

class Color {
   public:
     int red;
     int green;
     int blue;
};

class Step {
  public:
    Step(int red, int green, int blue, unsigned long time);
    Color target;
    unsigned long time;
};

Step::Step(int red, int green, int blue, unsigned long set_time){
  target.red = red;
  target.green = green;
  target.blue = blue;
  time = set_time;
};

Step show[3] = {Step(0,0,0,0),Step(1024,30,0,10000),Step(500,0,500,10000)};

class Propigation{
  public:
    
};

class Brolly {
   public:
     Brolly();
     int currentStep;
     int nextStep;
     int numberOfSteps;
     void setColor(int red,int green,int blue);
     void moveTowardTarget();
     void initalize(int red,int green, int blue,unsigned long timeToTarget);
     Color current_color;
     Color target_color;
     unsigned long lastSet;
     unsigned long initialTime;
     unsigned long transitionTime;
};

void Brolly::moveTowardTarget() {
     Serial.println("in mTT");
     unsigned long currentTime = millis();
     long elapsedTime = initialTime - currentTime;
     
     if (nextStep >= numberOfSteps){
       nextStep = 0;
     }
     else{
       nextStep++;
     }
     
     if (elapsedTime > show[currentStep].time){
         currentStep = 0;
//         initialTime = millis();
         Serial.print(millis());
         Serial.println("in if");
     }
       /*       if (currentStep >= numberOfSteps){
         currentStep = 0;
         Serial.println("Reset to beginning of show ");
       }
       else {
         currentStep++;
//         initialTime = millis();
         Serial.println("moved to next step");
       }
//       current_color.red = show[currentStep].target.red;
//       current_color.green = show[currentStep].target.green;
//       current_color.blue = show[currentStep].target.blue;
     }
     else {
       Serial.println("moved along step");
//       unsigned long ratio = elapsedTime;
//       current_color.red = current_color.red + (show[currentStep].target.red - show[nextStep].target.red)*(elapsedTime/show[currentStep].time);
//       current_color.red = show[currentStep].target.red+((show[currentStep].target.red - show[nextStep].target.red)*(elapsedTime/show[currentStep].time));
     }
*/     
};
 
Brolly::Brolly() {
     numberOfSteps = 3;
     currentStep = 0;
     nextStep = 1;
//  Grrr.  milis doesn't work in global constructors.
//     lastSet = millis();
//     initialTime = millis();
     current_color.red = 0;
     current_color.green = 0;
     current_color.blue = 0;
}; 

Brolly my_brollies[NumLEDs]; 
 
void Brolly::setColor(int red,int green,int blue) {
     current_color.red = red;
     current_color.blue = blue;
     current_color.green = green;
     lastSet = millis();
};



class Sculpture {
  public:
    void displayColors();
    void loadShow();
  private:
    Brolly brollies[NumLEDs];
};

void setup() {
   Serial.begin(9600);
   pinMode(datapin, OUTPUT);
   pinMode(latchpin, OUTPUT);
   pinMode(enablepin, OUTPUT);
   pinMode(clockpin, OUTPUT);
   SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(0<<SPR0);
   digitalWrite(latchpin, LOW);
   digitalWrite(enablepin, LOW);
   Serial.println("Brolly Flock Sequencer Setup Done.");
};
 
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
 
};
 
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
 
};

void setColor(int red,int green, int blue, int brolly){
   LEDChannels[brolly][0] = red;
   LEDChannels[brolly][1] = green;
   LEDChannels[brolly][2] = blue;   
};

void loop() {
   Brolly firstBrolly;
   firstBrolly.moveTowardTarget();
   setColor(1023,0,0,0); 
   setColor(0,0,0,1); 
   setColor(0,0,0,2); 
//   Serial.print("Red = ");
//   Serial.println(firstBrolly.current_color.red);
 
   WriteLEDArray();

   setColor(0,0,0,0); 
   setColor(1023,0,0,1); 
   setColor(0,0,0,2); 
//   Serial.println("Green");
 
   WriteLEDArray();
   
   setColor(0,0,0,0); 
   setColor(0,0,0,1); 
   setColor(1023,0,0,2); 
//   Serial.println("Blue");
   
   WriteLEDArray();
 
 
};


