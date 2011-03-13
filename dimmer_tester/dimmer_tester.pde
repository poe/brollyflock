#define dimmerPin 9

#define pot_minimum 0
#define pot_maximum 1023
#define pot_lower 341
#define pot_higher 682

#define pwm_maximum 255
#define pwm_minimum 0

int sensorPin0 = A0;    // select the input pin for the potentiometer
int sensorValue0 = 0;  // variable to store the value coming from the sensor
int sensorPin1 = A1;    // select the input pin for the potentiometer
int sensorValue1 = 0;  // variable to store the value coming from the sensor

void setup()
{
  pinMode(dimmerPin, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Starting dimmer test.");
  
}

void loop()
{
  
  int j;
  
  int directon = 0;

  sensorValue0 = analogRead(sensorPin0);    

// debugging prints
  Serial.println(sensorValue0); 
//  Serial.println(sensorValue1); 
  analogWrite(dimmerPin,sensorValue0 / 4); 
  
}

