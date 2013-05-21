#include <Wire.h>
#include <Bricktronics.h>

#define STOP_MOTOR_POWER  128
#define STOP_MOTOR_TIME   25

Bricktronics brick = Bricktronics();
Motor horMotor = Motor(&brick, 1); 
Motor verMotor = Motor(&brick, 2);
Button button = Button(&brick, 1);

int currentX = 0;
int currentY = 0;
boolean atBinPacker = false;

void moveRobot(int toX, int toY)
{
  int x = toX - currentX;
  int y = toY - currentY;


  if(x < 0)
  {
  }
  else
  {
    for(int _x=0;_x<x;_x++)
    {
      horMotor.set_speed(-64);
      waitFor(horMotor, 385);
      horMotor.set_speed(STOP_MOTOR_POWER);
      delay(STOP_MOTOR_TIME);
      horMotor.stop();
      delay(1000);
    }
  }

  currentX=toX;
  currentY=toY;
}

void moveToBinPacker()
{
  horMotor.set_speed(64);
  while(button.is_released());

  horMotor.set_speed(-STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);  
  horMotor.stop();
  
  atBinPacker= true;  
  
  delay(1000);
}

void moveToWarehouse()
{
  atBinPacker = false;
  
  horMotor.set_speed(-64);
  waitFor(horMotor, 700);
  horMotor.set_speed(STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);  
  horMotor.stop();
  
  delay(1000);
}

void waitFor(Motor m, int degrees)
{
  m.set_pos(0);
  delay(100);
  int sPos = m.get_pos();

  if(0 < degrees)
    while(m.get_pos() < sPos + degrees) delay(2);  
  else
    while(m.get_pos() > sPos + degrees) delay(2); 
    
    Serial.print("Done@");
    Serial.println(m.get_pos());
}

void setup()
{
  Serial.begin(9600);
  
  brick.begin();
  button.begin();
  horMotor.begin();

  moveToBinPacker();
  moveToWarehouse();
  moveRobot(2, 0);
}

void loop()
{

}



