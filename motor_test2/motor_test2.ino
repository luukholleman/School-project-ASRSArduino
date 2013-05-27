/*
 * Main code voor testen motor
 * @author Tim Potze
*/

#include <Wire.h>
#include <Bricktronics.h>

void setup()
{
  Serial.begin(9600);
  forkSetup();
  motorSetup();
   
  moveToBottom();
  
  //Syncs
  moveToBinPacker(); //Also a test
  
  
  //Pick up all products (test)
  
      moveToWarehouse();
      moveRobot(0, 0);
      pickup();
      moveToBinPacker();
      dropdown();
      
        
            moveToWarehouse();
      moveRobot(0, 1);
      pickup();
      moveToBinPacker();
      dropdown();
   
      
            moveToWarehouse();
      moveRobot(2, 0);
      pickup();
      moveToBinPacker();
      dropdown();
 
      
            moveToWarehouse();
      moveRobot(2, 1);
      pickup();
      moveToBinPacker();
      dropdown();
  
  //dropdown();
  
}

void loop()
{

}




