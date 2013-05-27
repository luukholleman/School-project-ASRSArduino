/*
 * Code om mindstorms motoren aan te sturen
 * @author Tim Potze
*/

#define HORIZONTAL_SPEED        128
#define HORIZONTAL_LOW_SPEED    32
#define MAX_HORIZONTAL_OFFSET   10

#define VERTICAL_SPEED          128
#define VERTICAL_LOW_SPEED      64
#define MAX_VERTICAL_OFFSET     22

#define DELAY_AFTER_MOVING      75
#define POLLING_DELAY           1

//Bricktronics. Awesome.
Bricktronics brick = Bricktronics();

Motor horMotor = Motor(&brick, 1); 
Motor verMotor = Motor(&brick, 2);

Button horButton = Button(&brick, 1);
Button verButton = Button(&brick, 2);

//Ga met motor naar pos met speed
void moveToPosition(Motor m, long pos, int speed, int lowSpeed, int maxOffset)
{
  //Als al binnen de offset, niks doen!
  if(abs(m.get_pos() - pos) < maxOffset)
    return;
    
  //Bereken of de snelheid vooruit of achteruit moet
  speed *= (pos > m.get_pos() ? -1 : 1);
 
  //Bereken aan welke kant van het doel de motor nu is
  boolean check = m.get_pos() > pos;

  //Beweeg, en wacht tot de motor aan de andere kant van het doel is
  m.set_speed(speed);  
  while((m.get_pos() > pos) == check) delay(POLLING_DELAY);   
  m.stop();
  
  //Wact even voor het uitrollen
  delay(60);
  
  //Probeer een maximum afweiking van MAX_MOTOR_OFFSET te krijgen)
  if(abs(m.get_pos() - pos) > maxOffset)
    moveToPosition(m, pos, lowSpeed, lowSpeed, maxOffset);
    
}

//Verplaats x posities met horMotor
void moveHorizontalPositions(long pos, int maxOffset)
{
   //Nutteloze dingen doen wij niet.
  if(pos == 0)
    return;
    
  //Ga naar doel toe
  moveToPosition(horMotor, horMotor.get_pos() + pos, HORIZONTAL_SPEED, HORIZONTAL_LOW_SPEED, maxoffset);
}

void moveHorizontalPositions(long pos)
{
  moveHorizontalPositions(pos, MAX_HORIZONTAL_OFFSET);
}

//Verplaats x posities met verMotor
void moveVerticalPositions(long pos, int maxOffset)
{
   //Nutteloze dingen doen wij niet.
  if(pos == 0)
    return;
    
  //Ga naar doel toe
  moveToPosition(verMotor, verMotor.get_pos() + pos, VERTICAL_SPEED, VERTICAL_LOW_SPEED, MAX_VERTICAL_OFFSET);
}

void moveVerticalPositions(long pos)
{
  moveVerticalPositions(pos, MAX_VERTICAL_OFFSET);
}

//Ga horizontaal naar het einde
void moveToHorizontalEnd()
{
  //Zet de motor aan totdat de knop aan is geraakt
  horMotor.set_speed(HORIZONTAL_SPEED);
  while(horButton.is_released()); 
  horMotor.stop();
}

//Ga verticaal naar het einde
void moveToVerticalEnd()
{
  //Zet de motor aan totdat de knop aan is geraakt
  verMotor.set_speed(-VERTICAL_SPEED);
  while(verButton.is_released()); 
  verMotor.stop();
}

void motorSetup()
{
  //Bricktronics
  brick.begin();
  
  //Buttons
  horButton.begin();
  verButton.begin();
  
  //Motoren
  horMotor.begin();
  verMotor.begin();

  //Zet de speed op 0
  horMotor.set_speed(0);
  verMotor.set_speed(0);
}
