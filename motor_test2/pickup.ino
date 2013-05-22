//Pak het product op
void pickup()
{
  //Fork uitschuiven
  extractFork();

  //Omhoog gaan
  verMotor.set_speed(128);
  waitFor(verMotor, -200);
  
  verMotor.set_speed(-STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);
  
  verMotor.stop();
  delay(1000);

  //Fork inschuiven
  withdrawFork();

  //Ga terug naar beneden
  resetHeight();
}

//Zet het product neer
void dropdown()
{
  //Omhoog gaan
  verMotor.set_speed(128);
  waitFor(verMotor, -150);
  verMotor.set_speed(-STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);
  verMotor.stop();
  delay(1000);

  //Doe de fork 500 ms naar voren
  extractFork(500);

  //Ga weer naar beneden
  verMotor.set_speed(-128);
  waitFor(verMotor, 150);
  verMotor.set_speed(-STOP_MOTOR_POWER);
  delay(STOP_MOTOR_TIME);
  verMotor.stop();
  delay(1000); 
  
  //Schijf de fork weer in
  withdrawFork();
}
