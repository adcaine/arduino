#include <Arduino.h>

namespace allanStarSoftware{

#define ARRAY_SIZE 10

class BarLED{

   public:

   BarLED(int* arrayIn);

   void operator++(int);

   void operator--(int);

   void setLevelTo(int);

   int getLevel() const;

   int getSize() const;

   private:

   void writeToDevice(int delta = 0);

   int _level;

   int _pins[ARRAY_SIZE];

};


} // end namespace allanStarSoftware
