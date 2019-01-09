#ifndef IM_TIMER_H
#define IM_TIMER_H

#include "Arduino.h"
#include "Wire.h"
#include "DS3231.h"

class IMTimer {
  private:
    static const char * extension = ".LOG";
    
    unsigned long startTime;
    unsigned long checkTime;
    unsigned long prevTime;

    DS3231 clock;
    RTCDateTime dt;

  public:
    IMTimer();

    unsigned long start();
    unsigned long check();
    unsigned long stop();
    String getLogStamp();
    String getFileName();
    
};

#endif
