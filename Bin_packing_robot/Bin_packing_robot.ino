// Declaratie lopende band
int transportingBeltDirectionPin = 4;
int transportingBeltMotorPin = 5;
int transportingBeltSpeed = 255;

// Declaratie draaischijf
int turningPlateDirectionPin = 7;
int turningPlateMotorPin = 6;
int turningPlateLeftSpeed = 255;
int turningPlateRightSpeed = 255;

// Vaste variabelen declaratie
byte currentBin = 0;


void setup() {                
  pinMode(transportingBeltDirectionPin, OUTPUT);
  pinMode(turningPlateDirectionPin, OUTPUT);
  pinMode(transportingBeltMotorPin, OUTPUT);
  pinMode(turningPlateMotorPin, OUTPUT);
  Serial.begin(9600);
  
  // Debug only: byte om aan te geven dat de connectie werkt
  Serial.write(100);
}


void loop() {
  
  // Checkt op commando's van de PC
  if(Serial.available() > 0){
    
    // Haalt de byte op die door JAVA is verzonden
    byte Byte = Serial.read();
    
    
    // Beweegt de lopende band naar de goede bin
    while(newBin != currentBin){
      if(newBin > currentBin){
        startTurningPlate("right");
        delay(1000);
        stopTurningPlate();
        currentBin = currentBin + 1;
      }
      
      if(newBin < currentBin){
        startTurningPlate("left");
        delay(1000);
        stopTurningPlate();
        currentBin = currentBin - 1;
      }
    }
    
    // Plaatst product in bin
    startTransportingBelt();
    delay(1000);
    stopTransportingBelt();
    
    // Geeft een bevestiging dat de opdracht is uitgevoerd: 101 is verzonnen
    Serial.write(101);
  }
}


// Functies
void startTransportingBelt(){
  analogWrite(transportingBeltMotorPin, transportingBeltSpeed);
  digitalWrite(transportingBeltDirectionPin, HIGH);
}

void stopTransportingBelt(){
  analogWrite(transportingBeltMotorPin, 0);
}

void startTurningPlate(String Direction){
  if(Direction == "left"){
    analogWrite(turningPlateMotorPin, turningPlateLeftSpeed);
    digitalWrite(turningPlateDirectionPin, LOW);
  }
  
  if(Direction == "right"){
    analogWrite(turningPlateMotorPin, turningPlateRightSpeed);
    digitalWrite(turningPlateDirectionPin, HIGH);
  }
}

void stopTurningPlate(){
  analogWrite(turningPlateMotorPin, 0);
}
