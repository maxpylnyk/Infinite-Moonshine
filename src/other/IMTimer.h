#ifndef IM_TIMER_H
#define IM_TIMER_H

#include "Arduino.h"

class IMTimer {
  private:
    bool active;
    unsigned long startTime;
    unsigned long checkTime;
    unsigned long prevTime;

  public:
    IMTimer();
    
    unsigned long start();
    unsigned long check();
    unsigned long getElapsedTime();
    unsigned long stop();
    
};

#endif
