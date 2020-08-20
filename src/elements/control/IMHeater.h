#ifndef IM_HEATER_H
#define IM_HEATER_H

#include "Arduino.h"
#include "stdint.h"
#include "other/IMConstants.h"


class IMHeater {
  private:
    uint8_t power;

  public:
    IMHeater();

    void setPower(uint8_t);
    uint8_t getPower();

};

#endif
