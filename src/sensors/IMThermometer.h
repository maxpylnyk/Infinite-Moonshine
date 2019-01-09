#ifndef IM_THERMOMETER_H
#define IM_THERMOMETER_H

#include "DallasTemperature.h"

class IMThermometer {
  private:
    float adjustment;
    float temperature;
    uint8_t * address;

  public:
    IMThermometer();

    void setAddress(uint8_t * value);
    void setAdjustment(float value);
    void setRawTemp(float value);
    float getTemperature();
    uint8_t * getAddress();

};

#endif
