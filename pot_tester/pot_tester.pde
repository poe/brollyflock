int sensorPin0 = A0;    // select the input pin for the potentiometer
int sensorValue0 = 0;  // variable to store the value coming from the sensor
int sensorPin1 = A1;    // select the input pin for the potentiometer
int sensorValue1 = 0;  // variable to store the value coming from the sensor

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting potentiometer test.");
}

void loop()
{
  sensorValue0 = analogRead(sensorPin0);    
  sensorValue1 = analogRead(sensorPin1);    
  Serial.println(sensorValue0); 
  Serial.println(sensorValue1); 
}

