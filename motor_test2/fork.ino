//Pinnen van de fork motor
#define FORK_SPEED_PIN    6
#define FORK_MOTOR_PIN    7

//Snelheid van de fork
#define FORK_SPEED        128

//Schuif de fork helemaal uit
void extractFork(){
  extractFork(1000);
}

//Schuif de fork uit
void extractFork(int time){
  //Rechtsom
  digitalWrite(FORK_MOTOR_PIN, LOW);
  
  //Schuif uit...
  analogWrite(FORK_SPEED_PIN, FORK_SPEED);
  delay(time);
  analogWrite(FORK_SPEED_PIN, 0);
}

//Schuif de fork helemaal in
void withdrawFork(){
  //Linksom
  digitalWrite(FORK_MOTOR_PIN, HIGH);
  
  //Schuif in...
  analogWrite(FORK_SPEED_PIN, FORK_SPEED);
  delay(1000);
  analogWrite(FORK_SPEED_PIN, 0);
}

void fork_setup()
{
  //Zet de pinnen in de juiste modus
  pinMode(FORK_MOTOR_PIN, OUTPUT);
  pinMode(FORK_SPEED_PIN, OUTPUT);
  
  //Schuif de fork helemaal in
  withdrawFork();
}
