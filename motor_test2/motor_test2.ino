#include <Wire.h>
#include <Bricktronics.h>

void setup()
{
  Serial.begin(9600);

  //fork_setup();
  motor_setup();
  
  delay(1000);
  
  //resetHeight();
  
  delay(1000);


  moveToBinPacker();
  moveToWarehouseNew();
  
  moveRobotNew(2, 1);
  //pickup();
  //moveToBinPacker();
  //dropdown();
}

void loop()
{

}




