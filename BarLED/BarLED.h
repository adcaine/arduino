/**
 Written by Allan Caine, August 4, 2013

 Suitable for use with Sparkfun products

 https://www.sparkfun.com/products/9935 (and their equivalents)

 https://www.sparkfun.com/products/11470 (ArduSensor Learning Kit)
**/

#include <Arduino.h>

namespace allanStarSoftware{

/**
 The number of LEDs in the Bar Graph
**/

#define ARRAY_SIZE 10

class BarLED{

   public:

      /**
       Pass in an array of 10 ints corresponding to the pins used by
       the LED bar graph.  The order must be bottom to top of the LED

       Example, to construct a BarLED object with Sparkfun's 
       Ardu Sensor Learning Kit
       https://www.sparkfun.com/products/11470/


       #include<BarLED.h>

       using namespace allanStarSoftware;

       int pinSetup[] = {A5, 2, 4, 7, 8, A4, 10, 11, 12, 13};

       BarLED bLED(pinSetup);

       void setup(){
          bLED.setLevelTo(0);
       }
      **/
       
      BarLED(int* arrayIn);


      /**
       Increases the number of lit LEDs by one.  If all of the LEDs are
       lit, the function does nothing.
       
       Example, if the object is bLED, then the code is
         bLED++;

      **/
       
      void operator++(int);


      /**
       Decreases the number of lit LEDs by one.  If all of the LEDs are
       off, the function does nothing.

       Example, if the object is bLED, then the code is

         bLED--;
      **/

      void operator--(int);


      /**
       Turns on the number of lit LEDs to level.  Use -1 to switch off all LEDs

       If the object is bLED, then

       bLED.setLevelTo(5);

       will switch on the bottom 5 LEDs and switch off the top 5 LEDs
      **/

      void setLevelTo(int level);


      /**
       Returns the number of LEDs currently lit

       bLED.getLevel();
      **/

      int getLevel() const;


      /**
       Returns the number of LEDs in the Bar graph.  Currently returns 10

      bLED.getSize();
      **/

      int getSize() const;

   private:

     /**
      Private method to write to the pins to switch on or off the correct
      LEDs
     **/
   
     void writeToDevice(int delta = 0);


     /**
      The number of lit LEDs
     **/

     int _level;


     /**
      The Arduino pins connected to the LEDs of the bar LED.  Order is
      important; bottom LED to top LED of the bar LED.
     **/

     int _pins[ARRAY_SIZE];

};


} // end namespace allanStarSoftware
