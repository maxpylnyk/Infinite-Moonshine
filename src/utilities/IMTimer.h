#ifndef IM_TIMER_H
#define IM_TIMER_H

#include "Arduino.h"
#include "Wire.h"
#include "DS3231.h"

class IMTimer {
  private:
    static const char * extension = ".LOG";
    bool active;
    unsigned long startTime;
    unsigned long checkTime;
    unsigned long prevTime;

    DS3231 clock;
    RTCDateTime dt;

  public:
    IMTimer();

    bool init();
    void setupTime();
    unsigned long start();
    unsigned long check();
    unsigned long getElapsedTime();
    unsigned long stop();
    String getTime();
    String getDate();
    String getLogStamp();
    String getFileName();
    float getEnvTemp();
    uint8_t getHH();
    uint8_t getMM();
    
};

#endif
