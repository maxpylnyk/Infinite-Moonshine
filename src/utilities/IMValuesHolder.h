#ifndef IM_VALUES_HOLDER_H
#define IM_VALUES_HOLDER_H

#include "utilities/IMCommons.h"
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

  public:
    IMValuesHolder(IMCondenserNode*, IMExtractionNode*, IMSwitchNode*, IMThermometers*);

    bool collectValues();
    void prepareToCollect();

    void setSwitchPos(uint8_t);
    void setHeatPwr(uint8_t);
    void setHeatAdj(uint8_t);
    void setCondMtrPos(int16_t);
    void setCondMtrAdj(int16_t);
    void setOutMtrPos(int16_t);
    void setRetMtrPos(int16_t);
    void setExtAdj(int16_t);
    void setRefluxRatio(float);

    uint8_t getSwitchPos();
    String getSwitchPosString();
    uint8_t getHeatPwr();
    uint8_t getHeatAdj();
    IMLevel getHydroLvl();
    String getHydroLvlString();
    uint16_t getAlcLvl();
    int16_t getCondMtrPos();
    int16_t getCondMtrAdj();
    int16_t getOutMtrPos();
    int16_t getRetMtrPos();
    int16_t getExtAdj();
    float getSteamTemp();
    float getCondTemp();
    float getPipeTemp();
    float getEnvTemp();
    float getCalcTemp();
    float getPressure();
    float getRefluxRatio();

    String getStateString();

};

#endif
