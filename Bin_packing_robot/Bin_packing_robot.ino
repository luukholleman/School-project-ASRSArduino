// Declaratie lopende band
#define TRANSPORTINGBELTDIRECTIONPIN 4
#define TRANSPORTINGBELTMOTORPIN 5
#define TRANSPORTINGBELTSPEED 200
#define TRANSPORTINGBELTDELAY 1000

// Declaratie draaischijf
#define TURNINGPLATEDIRECTIONPIN 7
#define TURNINGPLATEMOTORPIN 6
#define TURNINGPLATELEFTSPEED 200
#define TURNINGPLATERIGHTSPEED 200
#define TURNLEFTDELAY 500
#define TURNRIGHTDELAY 500

// Declaratie variabelen
#define STARTINGBIN 100
byte currentBin;


void setup() {                
  pinMode(TRANSPORTINGBELTDIRECTIONPIN, OUTPUT);
  pinMode(TRANSPORTINGBELTMOTORPIN, OUTPUT);
  pinMode(TURNINGPLATEDIRECTIONPIN, OUTPUT);
  pinMode(TURNINGPLATEMOTORPIN, OUTPUT);
  Serial.begin(9600);
  
  // Debug only: byte om aan te geven dat de connectie werkt
  Serial.write(100);
}


void loop() {
  
  // Checkt op commando's van de PC
  if(Serial.available() > 0){
    
    // Startlocatie
    currentBin = STARTINGBIN;
    
    // Haalt de byte op die door JAVA is verzonden
    byte newBin = Serial.read();
    
    // Beweegt de lopende band naar de goede bin
    turnToBin(newBin);
    
    // Plaatst product in bin
    startTransportingBelt();
    delay(TRANSPORTINGBELTDELAY);
    stopTransportingBelt();
    
    // Draait de lopende band terug naar de startpositie
    turnToBin(STARTINGBIN);
        
    // Geeft een bevestiging dat de opdracht is uitgevoerd: 101 is verzonnen
    Serial.write(101);
  }
}


// Functies
void startTransportingBelt(){
  analogWrite(TRANSPORTINGBELTMOTORPIN, TRANSPORTINGBELTSPEED);
  digitalWrite(TRANSPORTINGBELTDIRECTIONPIN, HIGH);
}

void stopTransportingBelt(){
  analogWrite(TRANSPORTINGBELTMOTORPIN, 0);
}

void startTurningPlate(String Direction){
  if(Direction == "left"){
    analogWrite(TURNINGPLATEMOTORPIN, TURNINGPLATELEFTSPEED);
    digitalWrite(TURNINGPLATEDIRECTIONPIN, LOW);
  }
  
  if(Direction == "right"){
    analogWrite(TURNINGPLATEMOTORPIN, TURNINGPLATERIGHTSPEED);
    digitalWrite(TURNINGPLATEDIRECTIONPIN, HIGH);
  }
}

void stopTurningPlate(){
  analogWrite(TURNINGPLATEMOTORPIN, 0);
}

void turnToBin(byte newBin){
  while(newBin != currentBin){
    if(newBin > currentBin){
      startTurningPlate("right");
      delay(TURNRIGHTDELAY);
      stopTurningPlate();
      currentBin = currentBin + 1;
    }
    
    if(newBin < currentBin){
      startTurningPlate("left");
      delay(TURNLEFTDELAY);
      stopTurningPlate();
      currentBin = currentBin - 1;
    }
  }
}
