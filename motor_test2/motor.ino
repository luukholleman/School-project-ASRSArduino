#define HORIZONTAL_SPEED    128
#define HORIZONTAL_LOW_SPEED  32
//Bricktronics. Awesome.
Bricktronics brick = Bricktronics();

Motor horMotor = Motor(&brick, 1); 
Motor verMotor = Motor(&brick, 2);

Button horButton = Button(&brick, 1);
Button verButton = Button(&brick, 2);

//Wacht voor motor m om degrees graden gedraaid te hebben
void waitFor(Motor m, long degrees)
{
  //Verkrijg de start positie
  long sPos = m.get_pos();

  //Als de graden onder 0 zijn, een andere behandeling geven
  if(0 < degrees)
    while(m.get_pos() < sPos + degrees) delay(2);  
  else
    while(m.get_pos() > sPos + degrees) delay(2); 

  //Debug
  Serial.print("waitFor END@");
  Serial.println(m.get_pos());
}

void moveToPosition(Motor m, long pos)
{
  moveToPosition(m, pos, HORIZONTAL_SPEED);
}

void moveToPosition(Motor m, long pos, int dirspeed)
{
  int speed = dirspeed * (pos > m.get_pos() ? -1 : 1);
 
  boolean check = m.get_pos() > pos;
  
  Serial.print("Moving at ");
  Serial.print(speed);
  Serial.print(" to ");
  Serial.print(pos);
  Serial.print(" from "); 
  Serial.print(m.get_pos());
  Serial.print(" check equals ");
  Serial.println(check);
  
  m.set_speed(speed);
  
  while((m.get_pos() >= pos) == check) delay(2);
    
  m.stop();
  
  delay(50);
  
  Serial.print("moveToPosition END@");
  Serial.println(m.get_pos());
  
  //Probeer een maximum afweiking van 10 te krijgen)
  Serial.println(abs(m.get_pos() - pos), DEC);
  
  if(abs(m.get_pos() - pos) > 10)
    moveToPosition(m, pos, HORIZONTAL_LOW_SPEED);
    
}

void movePositions(Motor m, long pos)
{
  moveToPosition(m, m.get_pos() + pos);
}

void moveHorizontalPositions(long pos)
{
  movePositions(horMotor, pos);
}

void moveToHorizontalEnd()
{
  horMotor.set_speed(HORIZONTAL_SPEED);
  while(horButton.is_released()); 
  horMotor.stop();
}

void motor_setup()
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
