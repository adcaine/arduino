#include <SPI.h>

namespace allanStarSoftware{

#define READ_SECS 0x00
#define READ_MINS 0x01
#define READ_HOUR 0x02
#define READ_DAY 0x03
#define READ_DATE 0x04
#define READ_MONTH 0x05
#define READ_YEAR 0x06
#define READ_ALM1_SECS 0x07
#define READ_ALM1_MINS 0x08
#define READ_ALM1_HRS 0x09
#define READ_ALM1_DAY 0x0A
#define READ_ALM2_MINS 0x0B
#define READ_ALM2_HRS 0x0C
#define READ_ALM2_DAY 0x0D
#define READ_CTRL1 0x0E
#define READ_CTRL2 0x0F
#define READ_CRYSTAL_OFFSET 0x10
#define READ_TEMP_MSB 0x11
#define READ_TEMP_LSB 0x12
#define READ_TEMP_CONV 0x13
#define READ_SRAM_ADDR 0x18
#define READ_DATA_ADDR 0x19

#define READ_TO_WRITE 0x80

#define WRITE_SECS (READ_SECS + READ_TO_WRITE)
#define WRITE_MINS (READ_MINS + READ_TO_WRITE)
#define WRITE_HRS (READ_HOUR + READ_TO_WRITE)
#define WRITE_DAY (READ_DAY + READ_TO_WRITE)
#define WRITE_DATE (READ_DATE + READ_TO_WRITE)
#define WRITE_MONTH (READ_MONTH + READ_TO_WRITE)
#define WRITE_YEAR (READ_YEAR + READ_TO_WRITE)
#define WRITE_ALM1_SECS (READ_ALM1_SECS + READ_TO_WRITE)
#define WRITE_ALM1_MINS (READ_ALM1_MINS + READ_TO_WRITE)
#define WRITE_ALM1_HRS (READ_ALM1_HRS + READ_TO_WRITE)
#define WRITE_ALM1_DAY (READ_ALM1_DAY + READ_TO_WRITE)
#define WRITE_ALM2_MINS (READ_ALM2_MINS + READ_TO_WRITE)
#define WRITE_ALM2_HRS (READ_ALM2_HRS + READ_TO_WRITE)
#define WRITE_ALM2_DAY (READ_ALM2_DAY + READ_TO_WRITE)
#define WRITE_CTRL1 (READ_CTRL1 + READ_TO_WRITE)
#define WRITE_CTRL2 (READ_CTRL2 + READ_TO_WRITE)
#define WRITE_CRYSTAL_OFFSET (READ_CRYSTAL_OFFSET + READ_TO_WRITE)
#define WRITE_TEMP_CONV (READ_TEMP_CONV + READ_TO_WRITE)
#define WRITE_SRAM_ADDR (READ_SRAM_ADDR + READ_TO_WRITE)
#define WRITE_DATA_ADDR (READ_DATA_ADDR + READ_TO_WRITE)

namespace Hourly{

enum Catagory{
  AM,
  PM,
  T24
};
} // end namespace Hourly

namespace Daily{
  
enum Catagory{
  Day,
  Date,
  DayAndDate
};

} // end namespace Daily

namespace Timely{

enum Catagory{
  ClockTime,
  Alarm1Time,
  Alarm2Time
};

} // end namespace timely

namespace Dately{

enum Catagory{
  ClockDate,
  Alarm1Date,
  Alarm2Date
};

} // end namespace Dately

struct Time{
   Timely::Catagory _timeCatagory;
   Hourly::Catagory _hourlyCategory;
   byte _hour;
   byte _minute;
   byte _second;
};  

struct Date{
  Dately::Catagory _dateCategory;
  Daily::Catagory _dailyCategory;
  byte _day;
  byte _date;
  byte _century;
  byte _month;
  byte _year;
};

class RTC{
  
  public:
  
    RTC(int slaveSelect) : _slaveSelectPin(slaveSelect){
      SPI.begin();
      SPI.setBitOrder(MSBFIRST); 
      SPI.setDataMode(SPI_MODE3); 
      pinMode(_slaveSelectPin, OUTPUT);
      //digitalWrite(_slaveSelectPin, HIGH);
    }

    int getSlaveSelectPin() const{
      return _slaveSelectPin;
    }
    
    float getTemp() const{
     float getFromRegister(READ_TEMP_LSB);
    }
    
    void getTime(Timely::Catagory category, Time& time){
      time._timeCatagory = category;
      byte hr = getHours(category);
      
      if((hr & 0x80) == 0){
        time._hourlyCategory = Hourly::T24;
      }else if((hr & 0x40) == 0){
        time._hourlyCategory = Hourly::AM;
      }else{
        time._hourlyCategory = Hourly::PM;
      }  
      
      time._hour = hr & 0x1F; 
      time._minute = getMinutes(category);
      time._second = getSeconds(category);
    }
    
    void getDate(Dately::Catagory category, Date& date){
    }
    
    
     
   private:
   
     unsigned int getFromRegister(int reg) const{
       digitalWrite(_slaveSelectPin, LOW);
       SPI.transfer(reg);
       unsigned int res = SPI.transfer(0x00);
       digitalWrite(_slaveSelectPin, HIGH);
       return res;
     }
    
     byte getHours(Timely::Catagory category){
       byte result = 0;
       switch(category){
         case Timely::ClockTime:
           result = getFromRegister(READ_HOUR);
           break;
         case Timely::Alarm1Time:
           result = getFromRegister(READ_ALM1_HRS);
           break;
         case Timely::Alarm2Time:
           result = getFromRegister(READ_ALM2_HRS);
           break;
       }
       return result;
     }   
    
     byte getMinutes(Timely::Catagory category){
       byte result = 0;
       switch(category){
         case Timely::ClockTime:
           result = getFromRegister(READ_MINS);
           break;
         case Timely::Alarm1Time:
           result = getFromRegister(READ_ALM1_MINS);
           break;
         case Timely::Alarm2Time:
           result = getFromRegister(READ_ALM2_MINS);
           break;
       }
       return result;
     }
     
     byte getSeconds(Timely::Catagory category){
       byte result = 0;
       switch(category){
         case Timely::ClockTime:
            result = getFromRegister(READ_SECS);
            break;
         case Timely::Alarm1Time:
            result = getFromRegister(READ_ALM1_SECS);
            break;
       }
       return result;
     }
     
     
   
       
 
     int _slaveSelectPin;  
};
}
allanStarSoftware::RTC clock(10);

byte fromBCDtoDEC(byte bdc){
 return ((bdc & 0x01F00) >> 4) + (bdc & 0x00FF);
} 

void loop(){
  /**
  digitalWrite(10, LOW);		
  SPI.transfer(0x01); 
  unsigned int n = SPI.transfer(0x00);
  Serial.println(n, HEX);
  Serial.println();
  digitalWrite(10, HIGH);
  delay(1000);
  **/
  allanStarSoftware::Time timeObj;
  
  clock.getTime(allanStarSoftware::Timely::ClockTime, timeObj);
  
  Serial.print(timeObj._hour, HEX);
  Serial.print(":");
  Serial.print(timeObj._minute, HEX);
  Serial.print(":");
  Serial.print(timeObj._second, HEX);
  Serial.print("  ");
  switch(timeObj._hourlyCategory){
    case allanStarSoftware::Hourly::AM:
    Serial.println("AM");
    break;
    case allanStarSoftware::Hourly::PM:
    Serial.println("PM");
    break;
    case allanStarSoftware::Hourly::T24:
    Serial.println("T24");
    break;
  }
  delay(1000);
}

void setup(){
  Serial.begin(9600);
      SPI.begin();
      SPI.setBitOrder(MSBFIRST); 
      SPI.setDataMode(SPI_MODE3); 
      //SPI.transfer(0x8E);
      //SPI.transfer(0x60); //60= disable Osciallator and Battery SQ wave @1hz, temp compensation, Alarms disabled
      pinMode(10, OUTPUT);
}
