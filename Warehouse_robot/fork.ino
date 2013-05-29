/*
 * Code om de fork aan te sturen
 * @author Tim Potze
*/

#define FORK_SPEED_PIN    6
#define FORK_MOTOR_PIN    7

#define FORK_SPEED        128

#define FORK_FULL_SLIDE   1000

//Schuif de fork uit
void slideForkOut(int time){
  //Rechtsom
  digitalWrite(FORK_MOTOR_PIN, LOW);
  
  //Schuif uit...
  analogWrite(FORK_SPEED_PIN, FORK_SPEED);
  delay(time);
  analogWrite(FORK_SPEED_PIN, 0);
}

void slideForkOut(){
  slideForkOut(FORK_FULL_SLIDE);
}


//Schuif de fork helemaal in
void slideForkIn(){
  //Linksom
  digitalWrite(FORK_MOTOR_PIN, HIGH);
  
  //Schuif in...
  analogWrite(FORK_SPEED_PIN, FORK_SPEED);
  delay(FORK_FULL_SLIDE);
  analogWrite(FORK_SPEED_PIN, 0);
}

void forkSetup()
{
  //Zet de pinnen in de juiste modus
  pinMode(FORK_MOTOR_PIN, OUTPUT);
  pinMode(FORK_SPEED_PIN, OUTPUT);
  
  //Schuif de fork helemaal in
  slideForkIn();
}
