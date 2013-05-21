#include <Wire.h>
#include <Bricktronics.h>

Bricktronics brick = Bricktronics();
Motor m = Motor(&brick, 1); 

int currentX = -2;
int currentY = 0;

#define SPEED_X      128
#define SPEED_Y      64
#define DEGREES_X    1000
#define DEGREES_Y    400

#define STOP_MOTOR_POWER  32128
#define STOP_MOTOR_TIME   25

void moveRobot(int toX, int toY)
{
  int x = toX - currentX;
  int y = toY - currentY;

  int degX = x * DEGREES_X;
}

int formulaX(int coords)
{
  //return 360;
  Serial.print("FormulaX: ");
  Serial.print((coords * 400) - 40,DEC);
  
  
  return (coords * 400) - 40;
}

void waitFor(int degrees)
{
  int sPos = m.get_pos();

  if(0 < degrees)
    while(m.get_pos() < sPos + degrees);  
  else
    while(m.get_pos() > sPos + degrees); 
}


void testA()
{
}


void testB()
{
}


void setup()
{
  Serial.begin(9600);
  Serial.println("Beginning");
  brick.begin();
  m.begin();

  m.set_speed(-SPEED_X);
  waitFor(formulaX(1));
  m.set_speed(STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);
  m.stop();

  delay(3000);


  //Turn 360 'degrees'
  m.set_speed(SPEED_X);
  waitFor(-formulaX(1));
  m.set_speed(-STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);
  m.stop();

}

void loop()
{

}

