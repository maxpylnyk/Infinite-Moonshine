#ifndef IM_TIME_H
#define IM_TIME_H

#include "Arduino.h"

class IMTime {
  public:
    IMTime();

    String getLogStamp();
    String getFileName();
    bool syncTime();
};

#endif
