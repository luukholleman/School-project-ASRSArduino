/*
 * Main code voor aansturen van warehouse robot
 * @author Tim Potze, Luuk Holleman, Bas van Koesveld, Mike van Loe
 */

#include <Wire.h>
#include <Bricktronics.h>

void setup()
{
  Serial.begin(9600);

  fork_setup();
  motor_setup();

  //Calibratie
  moveToBottom();
  moveToBinPacker();

  calibrationTest();


}

void loop()
{
  while(!Serial.available());

  int input = Serial.read();
}


void calibrationTest()
{
  moveToWarehouse();
  moveRobot(0, 0);
  
  delay(5000);
  moveRobot(1, 0);
  
  delay(5000);
  moveRobot(2, 0);
  
  delay(5000);
  moveRobot(3, 0);
   
}

/*
  
 --test code:
 
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
 
 */





