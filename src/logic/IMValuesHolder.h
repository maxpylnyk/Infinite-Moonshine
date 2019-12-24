#ifndef IM_VALUES_HOLDER_H
#define IM_VALUES_HOLDER_H

#include "utilities/IMConstants.h"
#include "sensors/IMSensor.h";
#include "sensors/IMHydroLevel.h"
#include "sensors/IMAlcoholSensor.h"
#include "sensors/IMBarometer.h"
#include "sensors/IMThermometers.h"
#include "control/IMHeater.h"
#include "control/IMStepMotor.h"
#include "control/IMSwitch.h"
#include "logic/IMCondenserNode.h"
#include "logic/IMExtractionNode.h"
#include "logic/IMSwitchNode.h"

class IMValuesHolder {
  private:
    IMCondenserNode * condNode;
    IMExtractionNode * extNode;
    IMSwitchNode * swNode;
    IMThermometers * trm;
    IMErrors * errors;

  public:
    IMValuesHolder(IMCondenserNode*, IMExtractionNode*, IMSwitchNode*, IMThermometers*);

    bool collectValues(bool);
    void prepareToCollect(bool);
    void setErrorList(IMErrors*);
    void setRefluxRatio(uint8_t);
    void setHeatPwr(uint8_t);
    void setHeatAdj(uint8_t);
    uint8_t getRefluxRatio();
    uint8_t getHeatPwr();
    uint8_t getHeatAdj();
    IMLevel getHydroLvl();
    uint16_t getAlcLvl();
    float getSteamTemp();
    float getCondTemp();
    float getPipeTemp();
    float getEnvTemp();
    float getCalcTemp();
    float getPressure();

    int16_t getWaterAdj();
    int16_t getExtAdj();
    void setWaterAdj(int16_t);
    void setExtAdj(int16_t);
    bool outMtrMoving();
    bool retMtrMoving();
    bool condMtrMoving();
    bool swMtrMoving();

    uint8_t getSwitchPos();
    int16_t getSwitchSteps();
    int16_t getSwitchTarget();
    int16_t getExtSpeed();
    int16_t getRefluxSpeed();
    int16_t getWaterSpeed();

    void setSwitchPos(uint8_t);
    void setExtSpeed(int16_t);
    void setRefluxSpeed(int16_t);
    void setWaterSpeed(int16_t);

    void restoreSwitch(uint8_t);
    void restoreExtSpeed(int16_t);
    void restoreRefluxSpeed(int16_t);
    void restoreWaterSpeed(int16_t);

};

#endif
