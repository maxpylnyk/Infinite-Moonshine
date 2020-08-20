#ifndef IM_SAVED_VALUES_H
#define IM_SAVED_VALUES_H

#include "Arduino.h"
#include "stdint.h"

class IMSavedValues {
  private:
    bool alcMeterEnabled;
    uint8_t heat;
    uint8_t hydroLvl;
    uint16_t alcLvl;
    float steamTemp;
    float condTemp;
    float pipeTemp;
    float envTemp;
    float pressure;

  public:
    IMSavedValues();

    bool useAlcMeter();
    uint8_t getHeat();
    uint8_t getHydroLvl();
    uint16_t getAlcLvl();
    float getSteamTemp();
    float getCondTemp();
    float getPipeTemp();
    float getEnvTemp();
    float getPressure();

    void enableAlcMeter(bool);
    void setHeat(uint8_t);
    void setHydroLvl(uint8_t);
    void setAlcLvl(uint16_t);
    void setSteamTemp(float);
    void setCondTemp(float);
    void setPipeTemp(float);
    void setEnvTemp(float);
    void setPressure(float);

};

#endif