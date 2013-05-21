#include <Wire.h>
#include <Bricktronics.h>
#include <ColorSensor.h>
 
//Bricktronics Example: ColorButton
//http://www.wayneandlayne.com/bricktronics
//When the button is pressed, a single reading from 
//the color sensor is taken and converted into a 
//color name and printed over the Serial Console.
 
//Connect a button to Sensor Port 1, and a Color 
//Sensor into Sensor Port 3.  Make sure to adjust 
//the jumpers on Sensor Port 3 so that only pins 3
// and 4 are connected.
 
Bricktronics brick = Bricktronics();
ColorSensor color = ColorSensor(&brick, 3); //Plug a Color Sensor 
                                            //into Sensor Port 3,
                                            //and adjust the 
                                            //jumpers so that
                                            //only pins 3 and 4 
                                            //are connected.
 
void setup() 
{
    Serial.begin(9600);
    brick.begin();
    color.begin(TYPE_COLORFULL);
}
 
void loop()
{   
  delay(500);
  color.print_color(color.get_color());
}

/**
* geeft de kleur terug in string, probeert 10 keer de kleur te lezen als het zwart is
*/
String readColor() {
  for(x = 0; x < 10; x++) {
    kleurtje = color.get_color();
    
    if(kleurtje != 'black') {
      break;
    }
    
    delay(500);
  }
  
  return kleurtje;
}
