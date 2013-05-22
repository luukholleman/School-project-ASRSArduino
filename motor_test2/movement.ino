//Power en time om de robot tot stilstand te laten komen
#define STOP_MOTOR_POWER  128
#define STOP_MOTOR_TIME   25

//Huidige locatie
int currentX = 0;
int currentY = 0;

//Is de robot bij de binpacker?
boolean atBinPacker = false;

//Ga naar XY...
void moveRobot(int toX, int toY)
{
  //Bereken verschil in huidige locatie en doel locatie
  int x = toX - currentX;
  int y = toY - currentY;

  //Als het doel negatief is, moet je andere code uitvoeren...
  if(x < 0)
  {
    for(int _x=0;_x<x;_x++)
    {
      horMotor.set_speed(128);
      waitFor(horMotor, 385);
      horMotor.set_speed(-STOP_MOTOR_POWER);
      delay(STOP_MOTOR_TIME);
      horMotor.stop();
      delay(1000);
    }
  }
  else
  {
    for(int _x=0;_x<x;_x++)
    {
      horMotor.set_speed(-128);
      waitFor(horMotor, 385);
      horMotor.set_speed(STOP_MOTOR_POWER);
      delay(STOP_MOTOR_TIME);
      horMotor.stop();
      delay(1000);
    }
  }

  //Zelfde hier
  if(y < 0)
  {
    for(int _y=0;_y<y;_y++)
    {
      verMotor.set_speed(-128);
      waitFor(verMotor, 365);
      verMotor.set_speed(STOP_MOTOR_POWER);
      delay(STOP_MOTOR_TIME);
      verMotor.stop();
      delay(1000);
    }
  }
  else
  {
    for(int _y=0;_y<y;_y++)
    {
      verMotor.set_speed(128);
      waitFor(verMotor, -365);
      verMotor.set_speed(-STOP_MOTOR_POWER);
      delay(STOP_MOTOR_TIME);
      verMotor.stop();
      delay(1000);
    }
  }
  
  //Sla de nieuwe locatie op
  currentX=toX;
  currentY=toY;
}

//Pak het product op
void pickup()
{
  //Fork uitschuiven
  extractFork();

  //Omhoog gaan
  verMotor.set_speed(128);
  waitFor(verMotor, -200);
  
  verMotor.set_speed(-STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);
  
  verMotor.stop();
  delay(1000);

  //Fork inschuiven
  withdrawFork();

  //Ga terug naar beneden
  resetHeight();
}

//Zet het product neer
void dropdown()
{
  //Omhoog gaan
  verMotor.set_speed(128);
  waitFor(verMotor, -150);
  verMotor.set_speed(-STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);
  verMotor.stop();
  delay(1000);

  //Doe de fork 500 ms naar voren
  extractFork(500);

  //Ga weer naar beneden
  verMotor.set_speed(-128);
  waitFor(verMotor, 150);
  verMotor.set_speed(-STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);
  verMotor.stop();
  delay(1000); 
  
  //Schijf de fork weer in
  withdrawFork();
}

//Ga naar de bin packer
void moveToBinPacker()
{
  //Ga helemaal naar voren tot dat de knop is aangeraakt
  horMotor.set_speed(128);
  while(horButton.is_released()); 
  horMotor.stop();

  //Sla op dat je bij de binpacker bent
  atBinPacker= true;  

  delay(1000);
}

//Ga naar de opslag(0,0)
void moveToWarehouse()
{
  //Sla op de je van de binpacker weg bent
  atBinPacker = false;

  //Ga 640 punten achteruit
  horMotor.set_speed(-128);
  waitFor(horMotor, 630);
  
  //Rem
  horMotor.set_speed(STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);  
  horMotor.stop();

  delay(1000);
}

//Ga helemaal naar beneden
void resetHeight()
{
  //Ga naar beneden tot de 
  verMotor.set_speed(-128);
  while(verButton.is_released());

  //Rem even
  verMotor.set_speed(128);
  waitFor(verMotor, -2);
  verMotor.stop();
  
}

