#ifndef IM_THERMOMETER_H
#define IM_THERMOMETER_H

#include "DallasTemperature.h"

class IMThermometer {
  private:
    float adjustment;
    float temperature;
    DeviceAddress address;

  public:
    IMThermometer();

    void setAddress(DeviceAddress value);
    void setAdjustment(float value);
    void setRawTemp(float value);
    float getTemperature();
    DeviceAddress getAddress();

};

#endif
