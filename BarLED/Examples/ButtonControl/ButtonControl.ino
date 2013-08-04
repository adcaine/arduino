#include <BarLED.h>

using namespace allanStarSoftware;

int pinSetup[] = {A5, 2, 4, 7, 8, A4, 10, 11, 12, 13};

boolean goingUp = true;

BarLED bled(pinSetup);

void setup(){
   pinMode(A0, INPUT);
   bled.setLevelTo(0);
};

void loop(){
   if(analogRead(A0) == 1023){
     changeBar();
   }
   delay(20);
}


void changeBar(){
  
  int level = bled.getLevel();
  
  if(level == -1){
    goingUp = true;
  }
  
  if(level == ARRAY_SIZE){
    goingUp = false;
  }
  
  if(goingUp){
    bled++;
  }else{
    bled--;
  }   
}  
