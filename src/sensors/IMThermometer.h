#ifndef IM_THERMOMETER_H
#define IM_THERMOMETER_H

#include "DallasTemperature.h"
#include "utilities/IMErrors.h"

class IMThermometer {
  private:
    bool measured;
    IMError error;
    float adjustment;
    float temperature;
    uint8_t * address;
    DallasTemperature * sensors;
    IMErrors * errors;

    void setMeasured(bool);
    void setSensors(DallasTemperature*);
    void setError(IMError);
    void setAddress(uint8_t*);
    void setAdjustment(float);
    void setRawTemp(float);

  public:
    IMThermometer(DallasTemperature * sensors, uint8_t * address, float adj, IMError error);

    float getTemperature();
    uint8_t * getAddress();
    void setErrorList(IMErrors*);
    bool receiveData();
    bool dataReady();

};

#endif
