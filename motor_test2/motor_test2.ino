#include <Wire.h>
#include <Bricktronics.h>

#define STOP_MOTOR_POWER  128
#define STOP_MOTOR_TIME   25

#define PWM_PIN            6
#define MOTOR_PIN          7

Bricktronics brick = Bricktronics();
Motor horMotor = Motor(&brick, 1); 
Motor verMotor = Motor(&brick, 2);
Button horButton = Button(&brick, 1);
Button verButton = Button(&brick, 2);

int currentX = 0;
int currentY = 0;
boolean atBinPacker = false;

void moveRobot(int toX, int toY)
{
  int x = toX - currentX;
  int y = toY - currentY;


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
  currentX=toX;
  currentY=toY;
}

void extractFork(){
  extractFork(1000);
}
void extractFork(int time){
  digitalWrite(MOTOR_PIN, LOW);
  analogWrite(PWM_PIN, 128);
  delay(time);
  analogWrite(PWM_PIN, 0);
}

void withdrawFork(){
  digitalWrite(MOTOR_PIN, HIGH);
  analogWrite(PWM_PIN, 128);
  delay(1000);
  analogWrite(PWM_PIN, 0);
}

void pickup()
{
  extractFork();

  verMotor.set_speed(128);
  waitFor(verMotor, -200);
  verMotor.set_speed(-STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);
  verMotor.stop();
  delay(1000);

  withdrawFork();

  resetHeight();
}

void dropdown()
{
  verMotor.set_speed(128);
  waitFor(verMotor, -150);
  verMotor.set_speed(-STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);
  verMotor.stop();
  delay(1000);

  extractFork(500);

  verMotor.set_speed(-128);
  waitFor(verMotor, 150);
  verMotor.set_speed(-STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);
  verMotor.stop();
  delay(1000); 
  
  withdrawFork();
}
void moveToBinPacker()
{
  horMotor.set_speed(128);
  while(horButton.is_released());

  horMotor.set_speed(-STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);  
  horMotor.stop();

  atBinPacker= true;  

  delay(1000);
}

void moveToWarehouse()
{
  atBinPacker = false;

  horMotor.set_speed(-128);
  waitFor(horMotor, 630);
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

void resetHeight()
{
  verMotor.set_speed(-128);
  while(verButton.is_released());

  verMotor.set_speed(128);
  waitFor(verMotor, -2);
  verMotor.stop();
  
}
void setup()
{
  Serial.begin(9600);

  brick.begin();
  horButton.begin();
  verButton.begin();
  horMotor.begin();
  verMotor.begin();

  horMotor.set_speed(0);
  verMotor.set_speed(0);

  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);

  withdrawFork();

  resetHeight();
  
  delay(1000);



  moveToBinPacker();
  moveToWarehouse();
  moveRobot(0, 0);
  pickup();
  moveToBinPacker();
  dropdown();
}

void loop()
{

}




