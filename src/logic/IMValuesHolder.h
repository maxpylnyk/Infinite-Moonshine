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
    void setRefluxRatio(uint8_t);
    void setHeatPwr(uint8_t);
    void setHeatAdj(uint8_t);
    void setCondMtrPos(uint16_t);
    void setCondMtrAdj(uint16_t);
    void setOutMtrPos(uint16_t);
    void setRetMtrPos(uint16_t);
    void setExtAdj(uint16_t);

    void setCondCurPos(uint16_t);
    void setOutCurPos(uint16_t);
    void setRetCurPos(uint16_t);
    void setSwCurPos(uint16_t);

    uint8_t getSwitchPos();
    uint8_t getRefluxRatio();
    uint8_t getHeatPwr();
    uint8_t getHeatAdj();
    IMLevel getHydroLvl();
    uint16_t getAlcLvl();
    uint16_t getCondMtrPos();
    uint16_t getCondMtrAdj();
    uint16_t getOutMtrPos();
    uint16_t getRetMtrPos();
    uint16_t getExtAdj();
    float getSteamTemp();
    float getCondTemp();
    float getPipeTemp();
    float getEnvTemp();
    float getCalcTemp();
    float getPressure();

};

#endif
