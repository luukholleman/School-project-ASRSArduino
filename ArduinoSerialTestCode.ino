void setup(){
  Serial.begin(9600);
  
  pinMode(13, OUTPUT);
}

void loop(){
  if(Serial.available()) {
    digitalWrite(13, HIGH);
    int input = Serial.read();
    
    if(input == 4){
      Serial.print(1);
    }
    else if(input == 1) {
      while(!Serial.available());
      int x = Serial.read();
      
      while(!Serial.available());
      int y = Serial.read();
      delay(5000);
      Serial.print(1);
      Serial.print(3);
    }
    else if(input == 2) {
      delay(1500);
      Serial.print(1);
    }
    else if(input == 3) {
      delay(1500);
      Serial.print(1);
    }
    else {
      Serial.print(1);
    }
    
    Serial.flush();
        
    delay(100);
    
    digitalWrite(13, LOW);
  }
}
