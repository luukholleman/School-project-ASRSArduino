/*
 * Main code voor testen motor
 * @author Tim Potze
*/

#include <Wire.h>
#include <Bricktronics.h>

void setup()
{
  Serial.begin(9600);
  fork_setup();
  motor_setup();
   
  moveToBottom();
  
  //Syncs
  moveToBinPacker(); //Also a test
  
  
  //Pick up all products (test)
  
  for(int y=0;y<2;y++)
  {
    for(int x=0;x<3;x++)
    {
      moveToWarehouse();
      moveRobot(x, y);
      pickup();
      moveToBinPacker();
      dropdown();
    }
  }
  
  
  //dropdown();
  
}

void loop()
{

}




