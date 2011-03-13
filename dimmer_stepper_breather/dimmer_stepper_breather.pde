#define stepPin 2
#define dirPin 3
#define enablePin 4

#define limitPin 5

int j;
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
  
    Serial.begin(9600);
  Serial.println("Starting potentiometer test.");

  // We set the enable pin to be an output
  pinMode(enablePin, OUTPUT);
  // then we set it HIGH so that the board is disabled until we
  // get into a known state
  digitalWrite(enablePin, HIGH);

//  Serial.begin(9600);
//  Serial.println("Starting stepper exerciser.");

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  digitalWrite(dirPin, HIGH);
  
  for(j=0; j<=10000; j++) {
//   Serial.println(digitalRead(limitPin));
    if(digitalRead(limitPin) == 0){
      digitalWrite(stepPin, LOW);
      delayMicroseconds(2);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(2000);
    }
  }


}

void loop(){

  delay(500);
  
  digitalWrite(dirPin, HIGH);
  
  for(j=0; j<=10000; j++) {
//   Serial.println(digitalRead(limitPin));
    if(digitalRead(limitPin) == 0){
      digitalWrite(stepPin, LOW);
      delayMicroseconds(2);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(2000);
      analogWrite(dimmerPin,j / 39); 
  //    Serial.println(j / 39);
    }
  }

  digitalWrite(dirPin, LOW);

  delay(500);

  for(j=0; j<=10000; j++) {
//   Serial.println(digitalRead(limitPin));
      digitalWrite(stepPin, LOW);
      delayMicroseconds(2);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(2000);
      analogWrite(dimmerPin,(10000 - j) / 39); 
//      Serial.println((10000 - j) / 39);
  }
  
}
