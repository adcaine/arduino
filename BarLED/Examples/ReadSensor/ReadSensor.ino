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


