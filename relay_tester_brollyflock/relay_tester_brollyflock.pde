

void setup(){
  for(int i = 0; i <=9 ; i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  } 
}

void loop(){
  for(int i = 2; i <=9; i++){
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW);
  }
  for(int i = 9; i >=2; i--){
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW);
  }
}
