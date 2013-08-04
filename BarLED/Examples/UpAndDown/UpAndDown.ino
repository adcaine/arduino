/**
Example for use with any 10-segment Bar LED.  For example

https://www.sparkfun.com/products/9935

The pinSetup array is the array to use with the Ardu Sensor kit

https://www.sparkfun.com/products/11470

#include <BarLED.h>

using namespace allanStarSoftware;

int pinSetup[] = {A5, 2, 4, 7, 8, A4, 10, 11, 12, 13};

BarLED bled(pinSetup);

void setup(){
   bled.setLevelTo(0);
};

void loop(){
  
  
  while(bled.getLevel() <= ARRAY_SIZE){
    bled++;
    delay(500);
  }

  while(bled.getLevel() >= 0){
     bled--;
     delay(500);
  }

};

