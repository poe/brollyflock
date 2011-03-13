#define limitPin 5

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting limit test.");
}

void loop()
{
  int sensorValue0;
  sensorValue0 = digitalRead(limitPin);    
  Serial.println(sensorValue0); 
}

