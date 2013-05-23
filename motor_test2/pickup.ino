/*
 * Code om producten te behandelen
 * @author Tim Potze
*/

#define PICKUP_HEIGHT            240
#define DROPDOWN_HEIGHT          500
#define BINPACKER_FORK_DISTANCE  500

//Pak het product op
void pickup()
{
  //Fork uitschuiven
  slideForkOut();
  
  //Omhoog gaan
  moveVerticalPositions(-PICKUP_HEIGHT);
  
  //Fork inschuiven
  slideForkIn();

  //Ga terug naar beneden
  moveVerticalPositions(PICKUP_HEIGHT);
}

//Zet het product neer
void dropDown()
{
  //Omhoog gaan
  moveVerticalPositions(-DROPDOWN_HEIGHT);

  //Doe de fork BINPACKER_FORK_DISTANCE ms naar voren
  slideForkOut(BINPACKER_FORK_DISTANCE);

  //Ga weer naar beneden
  moveToVerticalEnd();
  //moveToBottom();
  //moveVerticalPositions(DROPDOWN_HEIGHT);
  
  //Schijf de fork weer in
  slideForkIn();
  
  //Ga weer iets naar boven
  moveFromBottomToStartHeight();
}
