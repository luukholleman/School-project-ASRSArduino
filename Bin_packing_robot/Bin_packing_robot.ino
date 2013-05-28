// Declaratie lopende band
#define TRANSPORTING_BELT_DIRECTION_PIN 4
#define TRANSPORTING_BELT_MOTOR_PIN 5
#define TRANSPORTING_BELT_SPEED 200
#define TRANSPORTING_BELT_DELAY 1000

// Declaratie draaischijf
#define TURNING_PLATE_DIRECTION_PIN 7
#define TURNING_PLATE_MOTOR_PIN 6
#define TURNING_PLATE_LEFT_SPEED 255
#define TURNING_PLATE_RIGHT_SPEED 255
#define TURN_LEFT_DELAY 586
#define TURN_RIGHT_DELAY 950

// Declaratie variabelen
#define STARTING_BIN 0

#define DONE    3

#define LEFT    1
#define RIGHT   2

byte currentBin;


void setup() {                
  pinMode(TRANSPORTING_BELT_DIRECTION_PIN, OUTPUT);
  pinMode(TRANSPORTING_BELT_MOTOR_PIN, OUTPUT);
  pinMode(TURNING_PLATE_DIRECTION_PIN, OUTPUT);
  pinMode(TURNING_PLATE_MOTOR_PIN, OUTPUT);

  Serial.begin(9600);

  // Debug only: byte om aan te geven dat de connectie werkt
  Serial.write(DONE);
}


void loop() {

  // Checkt op commando's van de PC
  if(Serial.available() > 0){

    // Startlocatie
    currentBin = STARTING_BIN;

    // Haalt de byte op die door JAVA is verzonden
    int newBin = Serial.read();
     
    // Beweegt de lopende band naar de goede bin
    turnToBin(newBin);

    // Plaatst product in bin
    startTransportingBelt();
    delay(TRANSPORTING_BELT_DELAY);
    stopTransportingBelt();

    // Draait de lopende band terug naar de startpositie
    turnToBin(STARTING_BIN);

    // Geeft een bevestiging dat de opdracht is uitgevoerd: 101 is verzonnen
    Serial.write(DONE);
  }
}


// Functies
void startTransportingBelt(){
  analogWrite(TRANSPORTING_BELT_MOTOR_PIN, TRANSPORTING_BELT_SPEED);
  digitalWrite(TRANSPORTING_BELT_DIRECTION_PIN, HIGH);
}

void stopTransportingBelt(){
  analogWrite(TRANSPORTING_BELT_MOTOR_PIN, 0);
}

void startTurningPlate(int direction){
  if(direction == LEFT){
    analogWrite(TURNING_PLATE_MOTOR_PIN, TURNING_PLATE_LEFT_SPEED);
    digitalWrite(TURNING_PLATE_DIRECTION_PIN, HIGH);
  }

  if(direction == RIGHT){
    analogWrite(TURNING_PLATE_MOTOR_PIN, TURNING_PLATE_RIGHT_SPEED);
    digitalWrite(TURNING_PLATE_DIRECTION_PIN, LOW);
  }
}

void stopTurningPlate(){
  analogWrite(TURNING_PLATE_MOTOR_PIN, 0);
}

void turnToBin(int newBin){
  while(newBin != currentBin){
    if(newBin < currentBin){

      startTurningPlate(LEFT);
      delay(TURN_LEFT_DELAY);
      stopTurningPlate();

      currentBin--;
    }
    else if(newBin > currentBin){

      startTurningPlate(RIGHT);
      delay(TURN_RIGHT_DELAY);
      stopTurningPlate();

      currentBin++;
    }
  }
}

