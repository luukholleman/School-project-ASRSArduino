/*
 * Code om naar een locatie te gaan
 * @author Tim Potze
*/

//Power en time om de robot tot stilstand te laten komen
#define HOR_MOTOR_POINTS               425
#define VER_MOTOR_POINTS               -770

#define VERTICAL_BOTTOM_HEIGHT         -138
#define DISTANCE_BETWEEN_DEPARTMENTS   833

//Huidige locatie
int currentX = 0;
int currentY = 0;

//Is de robot bij de binpacker?
boolean atBinPacker = false;

void moveRobot(int toX, int toY)
{
  //Wanneer je bij de binapcker bent, ga daar van weg!
  if(!atBinPacker)
    moveToWarehouse();
    
  //Bereken verschil in huidige locatie en doel locatie  
  int moveX = toX - currentX;
  int moveY = toY - currentY;
  
  //Bereken posities om te bewegen
  long horPos = HOR_MOTOR_POINTS * moveX;
  long verPos = VER_MOTOR_POINTS * moveY;
  
  //Verplaats
  moveHorizontalPositions(horPos);
  moveVerticalPositions(verPos);
  
  //Sla nieuwe position op
  currentX = toX;
  currentY = toY;
}

//Ga naar de opslag(0, 0)
void moveToWarehouse()
{
  //Ga alleen als je er nog niet bent
  if(atBinPacker)
    moveHorizontalPositions(DISTANCE_BETWEEN_DEPARTMENTS);
    
    //Sla op dat je er bent
    atBinPacker = false;
}

//Ga naar de bin packer
void moveToBinPacker()
{
  //Stop als je er al bent
  if(atBinPacker)
    return;
    
  //Ga eerst naar 0, 0, mist je daar al bent
  moveRobot(0, 0);
  
  //Ga naar het einde
  moveToHorizontalEnd();
  
  //Wacht tot stilstand
  delay(1000); //fix dit!
  
  //Sla op dat je bij de binpacker bent
  atBinPacker= true;  
}

//Ga helemaal naar beneden
void moveToBottom()
{
  moveToVerticalEnd();
  moveFromBottomToStartHeight();
}

void moveFromBottomToStartHeight()
{
  moveVerticalPositions(VERTICAL_BOTTOM_HEIGHT); 
}


