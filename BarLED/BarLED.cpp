#include <BarLED.h>

using namespace allanStarSoftware;

BarLED::BarLED(int* arrayIn) : _level(0){
   for(int i = 0; i < ARRAY_SIZE; i++){
      _pins[i] = arrayIn[i];
      pinMode(_pins[i], OUTPUT);
   }
}

void BarLED::operator++(int){
   writeToDevice(1);
}

void BarLED::operator--(int){
   writeToDevice(-1);
}

int BarLED::getLevel() const{
   return _level;
}

int BarLED::getSize() const{
   return ARRAY_SIZE;
}

void BarLED::setLevelTo(int newLevel){
   _level = newLevel;
   writeToDevice();
}

void BarLED::writeToDevice(int delta){
   _level += delta;
   _level = constrain(_level, -1, ARRAY_SIZE +1);

   for(int i = 0; i < ARRAY_SIZE; i++){
      digitalWrite(_pins[i], i <= _level ? HIGH : LOW);
   }
}
