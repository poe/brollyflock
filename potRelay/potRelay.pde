//#define POTPIN 2
int potPin = 2;    // select input pin for potentiometer
int relayPin = 2;   // select pin for relay
int sensorVal = 0;       // variable to store the value coming from the sensor
byte i = 0;
boolean debug=false;

void setup() {
  pinMode(relayPin, OUTPUT);  // declare the relay as OUTPUT
}

void loop() {
  sensorVal = analogRead(potPin);    // read the value from the pot
  if (debug){
    if (i == 255){
      Serial.print("Value");
      Serial.println(sensorVal);
    }
    i++;
  }
   
  if (sensorVal < 200) {
    digitalWrite(relayPin, HIGH);  // keep valve open constant if the knob is low
  }
  else if (sensorVal > 600) {          // keep valve open if rate is too high
    digitalWrite(relayPin, HIGH); 
  }
  else{
    digitalWrite(relayPin, HIGH);   // turn the relayPin on
    delay(sensorVal);              // stop sensorVal amnt of time
    digitalWrite(relayPin, LOW);   // turn relayPin off
    delay(sensorVal);          
  }
 
}
