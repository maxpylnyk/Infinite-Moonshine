#ifndef IM_HARDWARE_INTERFACE_H
#define IM_HARDWARE_INTERFACE_H

#include "other/IMConstants.h"
#include "elements/sensors/IMSensor.h";
#include "elements/sensors/IMHydroLevel.h"
#include "elements/sensors/IMAlcoholSensor.h"
#include "elements/sensors/IMBarometer.h"
#include "elements/sensors/IMThermometers.h"
#include "elements/control/IMHeater.h"
#include "elements/control/IMStepMotor.h"

class IMHardwareInterface {
  private:
    IMHydroLevel * hlvl;
    IMAlcoholSensor * alc;
    IMThermometers * trm;
    IMBarometer * bar;
    IMHeater * heater;
    IMStepMotor * outMtr;
    IMStepMotor * retMtr;
    IMStepMotor * condMtr;
    IMStepMotor * swMtr;
    IMErrors * errors;

  public:
    IMHardwareInterface(IMHydroLevel*, IMAlcoholSensor*, IMThermometers*,
     IMBarometer*, IMHeater*, IMStepMotor*, IMStepMotor*, IMStepMotor*, 
     IMStepMotor*);

    bool collectValues(bool);
    void prepareToCollect(bool);
    void setErrorList(IMErrors*);

    uint8_t getHeat();
    IMLevel getHydroLvl();
    uint16_t getAlcLvl();
    float getSteamTemp();
    float getCondTemp();
    float getPipeTemp();
    float getEnvTemp();
    float getCalcTemp();
    float getPressure();
    
    void setHeat(uint8_t);
    void changeOutMtrPosOn(int32_t);
    void changeRetMtrPosOn(int32_t);
    void changeCondMtrPosOn(int32_t);
    void changeSwitchPosOn(int32_t);
    
    bool outMtrMoving();
    bool retMtrMoving();
    bool condMtrMoving();
    bool swMtrMoving();

    

};

#endif
