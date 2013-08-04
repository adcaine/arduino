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


