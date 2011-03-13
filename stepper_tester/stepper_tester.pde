#define stepPin 2
#define dirPin 3
#define enablePin 4
#define limitPin 5

#define pot_minimum 0
#define pot_maximum 1023
#define pot_lower 341
#define pot_higher 682

#define min_delay 2000

#define max_turns 50
#define steps_per_turn 200

#define forward HIGH
#define backward LOW

long max_steps = max_turns * steps_per_turn;
long motor_position;

int step_delay = min_delay;

int sensorPin0 = A0;    // select the input pin for the potentiometer
int sensorValue0 = 0;  // variable to store the value coming from the sensor
int sensorPin1 = A1;    // select the input pin for the potentiometer
int sensorValue1 = 0;  // variable to store the value coming from the sensor

int step_direction = 2;

void setup()
{
  // We set the enable pin to be an output
  pinMode(enablePin, OUTPUT);
  
  // Set the limit switch pin to be an input
  pinMode(limitPin, INPUT);
  
  // then we set it HIGH so that the board is disabled until we
  // get into a known state
  digitalWrite(enablePin, HIGH);

//  Serial.begin(9600);
//  Serial.println("Starting stepper exerciser.");

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Starting stepper test.");

  digitalWrite(dirPin, forward);
  step_direction = 1;  
  if(digitalRead(limitPin) == 0);
  for(int i;i<=100;i++) {
    take_step(min_delay);
  }
  motor_position = 0;
}

void loop()
{
  
  int j;
  // set the enablePin ow so that we can now use out stepper driver.
  digitalWrite(enablePin, LOW);
  // wait a few microseconds for the enable to take effect
  // (That isn't in the spec sheet I just added it for sanity.)
  delayMicroseconds(2);
  // we set the direction pin i an arbitrary direction.
  
  sensorValue0 = analogRead(sensorPin0);    
  sensorValue1 = analogRead(sensorPin1);    

// debugging prints
//  Serial.println(sensorValue0); 
//  Serial.println(sensorValue1); 
// Serial.println(digitalRead(limitPin));

  if(sensorValue0 > pot_higher){
    step_direction=1;
    digitalWrite(dirPin, forward);
    step_delay = (sensorValue0 - pot_higher) * 10 + min_delay;
    if (motor_position > 0){
      take_step(step_delay);
      motor_position--;
    }
  }
  else if(sensorValue0 < pot_lower){
    step_direction=2;
    digitalWrite(dirPin, backward);
    step_delay = (pot_lower - sensorValue0) * 10 + min_delay;
    if (motor_position < max_steps){
      take_step(step_delay);
      motor_position++;
    }
  }
  else {
    step_direction=0;
  }
  
}

void take_step(int step_delay){
//  Serial.print("step direction = ");
//  Serial.print(step_direction);
//  Serial.print(" limit pin = ");
//  Serial.println(digitalRead(limitPin));
  if(step_direction == 2 or digitalRead(limitPin) == 0){
//    Serial.println("taking step");
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2);
    digitalWrite(stepPin, HIGH);
//    Serial.print("step delay = ");
//    Serial.println(step_delay);
    delayMicroseconds(step_delay);
  }
}

