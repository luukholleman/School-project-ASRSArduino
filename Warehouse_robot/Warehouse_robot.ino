/*
 * Main code voor aansturen van warehouse robot
 * @author Tim Potze, Luuk Holleman, Bas van Koesveld, Mike van Loe
 */

#include <Wire.h>
#include <Bricktronics.h>

#define PICKUP_PRODUCT     1
#define DELIVER_PRODUCT    2
#define DONE               3

void setup()
{
  Serial.begin(9600);

  forkSetup();
  motorSetup();

  //Calibratie
  moveToBottom();
  moveToBinPacker();

  //calibrationTest();
}

void loop()
{
  while(!Serial.available());

  //Verwerk commando
  byte command = Serial.read();

  //Voor het debuggen is het mogelijk om chars '0' - '9' te gebruiken
  if(command >= '0' && command <= '9')
    command -= '0';
    
    
  byte x;
  byte y;
  
  switch(command)
  { 
  case PICKUP_PRODUCT:
    
    //Wacht op x
    while(!Serial.available());
    x = Serial.read();

    //Wacht op y
    while(!Serial.available());
    y = Serial.read();

    //Pak dit product op
    moveToWarehouse();
    moveRobot(x, y);
    pickUp();

    //Stuur kleur terug
    Serial.write(readColor());
    break;
  case DELIVER_PRODUCT:
    //Lever product af
    moveToBinPacker();
    dropDown();
    break;
  case DONE:
    //Ga naar start positie
    moveToBinPacker();
    break;
  }

  //Stuur voltooi bericht
  Serial.write(DONE);
}


void calibrationTest()
{
  moveToWarehouse();
  moveRobot(0, 0);
  pickUp();
  moveToBinPacker();
  dropDown();

  moveToWarehouse();
  moveRobot(3, 0);
  pickUp();
  moveToBinPacker();
  dropDown();

  moveToWarehouse();
  moveRobot(0, 2);
  pickUp();
  moveToBinPacker();
  dropDown();

  moveToWarehouse();
  moveRobot(3, 2);
  pickUp();
  moveToBinPacker();
  dropDown();

}







