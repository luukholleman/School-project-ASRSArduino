//Bricktronics. Awesome.
Bricktronics brick = Bricktronics();

Motor horMotor = Motor(&brick, 1); 
Motor verMotor = Motor(&brick, 2);

Button horButton = Button(&brick, 1);
Button verButton = Button(&brick, 2);

//Wacht voor motor m om degrees graden gedraaid te hebben
void waitFor(Motor m, int degrees)
{
  //Verkrijg de start positie
  int sPos = m.get_pos();

  //Als de graden onder 0 zijn, een andere behandeling geven
  if(0 < degrees)
    while(m.get_pos() < sPos + degrees) delay(2);  
  else
    while(m.get_pos() > sPos + degrees) delay(2); 

  //Debug
  Serial.print("waitFor END@");
  Serial.println(m.get_pos());
}

void motor_setup()
{
  //Bricktronics
  brick.begin();
  
  //Buttons
  horButton.begin();
  verButton.begin();
  
  //Motoren
  horMotor.begin();
  verMotor.begin();

  //Zet de speed op 0
  horMotor.set_speed(0);
  verMotor.set_speed(0);
}
