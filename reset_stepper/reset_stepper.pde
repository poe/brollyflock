#define stepPin 2
#define dirPin 3
#define enablePin 4

#define limitPin 5

void setup()
{
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
}

int j;

void loop(){
  digitalWrite(dirPin, HIGH);
  
  for(j=0; j<=1000; j++) {
//   Serial.println(digitalRead(limitPin));
    if(digitalRead(limitPin) == 0){
      digitalWrite(stepPin, LOW);
      delayMicroseconds(2);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(2000);
    }
  }
}
