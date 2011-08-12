// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
 
#define FADESPEED 5     // make this higher to slow down
 
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}
 
 
void loop() { 
  int val; 
  val = analogRead(3);
  val = map(val, 0, 1023, 0, 255);
  analogWrite(REDPIN, val);

  val = analogRead(4);
  val = map(val, 0, 1023, 0, 255);
  analogWrite(GREENPIN, val);

  val = analogRead(5);
  val = map(val, 0, 1023, 0, 255);
  analogWrite(BLUEPIN, val);
  
}
