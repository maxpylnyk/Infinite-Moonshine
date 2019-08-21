#ifndef IM_THERMOMETERS_H
#define IM_THERMOMETERS_H

#include "sensors/IMSensor.h"
#include "sensors/IMThermometer.h"
#include "utilities/IMErrors.h"
#include "OneWire.h"
#include "DallasTemperature.h"

class IMMega;

class IMThermometers : public IMSensor {
  private:
    static const uint8_t thermometersCount = 4;
    static const uint8_t resolution = 12;
    static const unsigned int initTime = 430;
    static const unsigned int requestTime = 675;
    static const unsigned int receiveTime = 100;

    float steamAdj = 0.0;
    float pipeAdj = 0.0;
    float condAdj = 0.0;
    float envAdj = 0.0;

    DeviceAddress steamAddr = {0x28, 0xFF, 0xD8, 0xC9, 0x33, 0x18, 0x02, 0x9E};
    DeviceAddress pipeAddr = {0x28, 0xFF, 0x6E, 0xD4, 0x33, 0x18, 0x01, 0x0A};
    DeviceAddress condAddr = {0x28, 0xFF, 0x7E, 0x00, 0x34, 0x18, 0x01, 0x03};
    DeviceAddress envAddr = {0x28, 0xFF, 0x43, 0xD6, 0x33, 0x18, 0x01, 0x19};

    OneWire wire = OneWire(TRM_PIN);
    DallasTemperature sensors = DallasTemperature(&wire);
    IMErrors * errors;
    IMThermometer steamTrm = IMThermometer(&sensors, steamAddr, steamAdj, IMError::NO_STEAM_TRM);
    IMThermometer pipeTrm = IMThermometer(&sensors, pipeAddr, pipeAdj, IMError::NO_PIPE_TRM);
    IMThermometer condTrm = IMThermometer(&sensors, condAddr, condAdj, IMError::NO_COND_TRM);
    IMThermometer envTrm = IMThermometer(&sensors, envAddr, envAdj, IMError::NO_ENV_TRM);

    IMThermometer trms[thermometersCount] = {steamTrm, pipeTrm, condTrm, envTrm};
    
    void printAddress(const uint8_t*);

  public:
    IMThermometers();

    bool init();
    void debug();
    void requestData();
    void receiveData();
    void setErrorList(IMErrors*);
    float getSteamTemp();
    float getPipeTemp();
    float getCondTemp();
    float getEnvTemp();
    IMThermometer* getSteamTrm();
    IMThermometer* getCondTrm();
    IMThermometer* getPipeTrm();
    IMThermometer* getEnvTrm();

};

#endif
