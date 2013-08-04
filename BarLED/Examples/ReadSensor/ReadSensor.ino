/**
Example for use with the Ardu Sensor Kit

http://www.sparkfun.com/products/11470

The force sensor is assumed to be plugged into A3

The bar graph will go up when the force sensor is pinched.

The bar graph will go down when the force sensor is released.
**/

#include <BarLED.h>

using namespace allanStarSoftware;

int pinSetup[] = {A5, 2, 4, 7, 8, A4, 10, 11, 12, 13};

BarLED bled(pinSetup);

void setup(){
   pinMode(A3, INPUT);
   bled.setLevelTo(0);
};

void loop(){
  bled.setLevelTo(map(analogRead(A3),0, 1023, -1, ARRAY_SIZE));
}  

