#include <Wire.h>
#include <Bricktronics.h>

#define STOP_MOTOR_POWER  128
#define STOP_MOTOR_TIME   25

Bricktronics brick = Bricktronics();
Motor horMotor = Motor(&brick, 1); 
Motor verMotor = Motor(&brick, 2);

int currentX = 0;
int currentY = 0;

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
      horMotor.set_speed(-128);
      waitFor(horMotor, 500);
      horMotor.set_speed(STOP_MOTOR_POWER);
      delay(STOP_MOTOR_TIME);
      horMotor.stop();
    }
  }
  
  currentX=toX;
  currentY=toY;
}

void waitFor(Motor m, int degrees)
{
  int sPos = m.get_pos();

  if(0 < degrees)
    while(m.get_pos() < sPos + degrees);  
  else
    while(m.get_pos() > sPos + degrees); 
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Beginning");
  brick.begin();
  horMotor.begin();

  moveRobot(1, 0);
}

void loop()
{

}


