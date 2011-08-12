//These are the defines for the pin to:
//take a step, 
//change direction and 
//enable the motor.  (note that the enable pin isn't wired up)
#define stepPin 2
#define dirPin 3
#define enablePin 4

#define minStepDelay 1000

//This is the input pin for the limit switch
#define limitPin 5

//This is the output pin for the velleman dimmer
#define dimmerPin 9

//These are the limits for the knobs.  
//minimum is the lowest value possible.
//maximum is the highest value possible.
//The area between lower and higher is a small 'dead zone'
#define pot_minimum 0
#define pot_maximum 1023
#define pot_lower 341
#define pot_higher 682

//These define the range for the pulses that go to the dimmer
#define pwm_maximum 255
#define pwm_minimum 0

//These are the pins for the valves.  in inflates, out deflates.
#define inValvePin 6
#define outValvePin 7  

int j;  //iterator

int sensorPin0 = A0;    // select the input pin for the potentiometer
int sensorValue0 = 0;  // variable to store the value coming from the sensor
int sensorPin1 = A1;    // select the input pin for the potentiometer
int sensorValue1 = 0;  // variable to store the value coming from the sensor

void setup()
{
  
  //This is left in place for debugging output
  Serial.begin(9600);
  Serial.println("Starting Breathing Program.");

  //Here we set all the right pin modes;  
  //See the defines above for what they do.
  pinMode(enablePin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(dimmerPin, OUTPUT);
  pinMode(inValvePin, OUTPUT);
  pinMode(outValvePin, OUTPUT);
  pinMode(limitPin, INPUT);

  // then we set it HIGH so that the board is disabled until we
  // get into a known state (though it is unwired)
  digitalWrite(enablePin, HIGH);
  
  // We set the dir pin to high so it starts in a forward motion
  digitalWrite(dirPin, HIGH);
  
  //Here is a loop that pushes the motor until 
  //the butterfly valve is in the closed position
  for(j=0; j<=10000; j++) {
    //We only actually step if the limit switch is open
    //Note that there will be almost no delay once is closes
    if(digitalRead(limitPin) == 0){
      //These four instructions take a step, 
      //then delay the minimum time before a new step can happen
      digitalWrite(stepPin, LOW);
      delayMicroseconds(2);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(minStepDelay);
    }
    //end limit switch if
  }
  //end initial step loop
}
//end setup

void loop(){

  //Here we close both air valves during the delay at the top
  digitalWrite(inValvePin,LOW);
  digitalWrite(outValvePin,LOW);

  //Here we delay at the top of the breath
  sensorValue1 = analogRead(sensorPin1);
  delay(sensorValue1 * 2);

  //Now we begin the exhale
  digitalWrite(inValvePin,HIGH);
  digitalWrite(outValvePin,LOW);

  //Sets the direction to forward  
  digitalWrite(dirPin, HIGH);
  
  //This is a loop that goes 50 turns, opening the butterfly valve
  //(200 steps per turn)
  for(j=0; j<=10000; j++) {
    //We only actually step if the limit switch is open
    //Note that there will be almost no delay once is closes
    if(digitalRead(limitPin) == 0){
      //Here we read the pot so we can figure out how big the step delay is
      sensorValue0 = analogRead(sensorPin0);
      //These four instructions take a step, 
      //then delay the minimum time before a new step can happen
      digitalWrite(stepPin, LOW);
      delayMicroseconds(2);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(minStepDelay + (sensorValue0 * 2));
      //Here we set the dimmer pwm pin to a value related to how 
      //Far along we are in the loop.
      //Note that if the number of steps is adjusted, this 
      //must also be adjusted
      //Note that this one counts up as j increases.
      //Because it is an int it will automatically round down
      analogWrite(dimmerPin,j / 39); 
    }
  }

  //Here we change direction in the stepper motor
  digitalWrite(dirPin, LOW);

  //Here we close both air valves at the bottom of the breath
  digitalWrite(inValvePin,LOW);
  digitalWrite(outValvePin,LOW);

  //This delays at the bottom of the breath
  sensorValue1 = analogRead(sensorPin1);
  delay(sensorValue1 * 2);

  //Here we open the exhale valve and close the inhale valve.  
  digitalWrite(inValvePin,LOW);
  digitalWrite(outValvePin,HIGH);

  //This is a loop that goes 50 turns, opening the butterfly valve
  //(200 steps per turn)
  for(j=0; j<=10000; j++) {
    //We step here regardless of the limit switch because 
    //otherwise we would never escape the place where it is closed
      //Here we read the pot so we can figure out how big the step delay is
      sensorValue0 = analogRead(sensorPin0);
      //These four instructions take a step, 
      //then delay the minimum time before a new step can happen
      digitalWrite(stepPin, LOW);
      delayMicroseconds(2);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(minStepDelay + (sensorValue0 * 2));
      //Here we set the dimmer pwm pin to a value related to how 
      //Far along we are in the loop.
      //Note that if the number of steps is adjusted, this 
      //must also be adjusted
      //Because it is an int it will automatically round down
      //Note that this one counts down as j increases
      analogWrite(dimmerPin,(10000 - j) / 39); 
  }
  //end stepper loop
  
}
//end main loop
