#ifndef IM_SESSION_H
#define IM_SESSION_H

#include "Arduino.h"
#include "stdint.h"
#include "utilities/IMCommons.h"

class IMSession {
  private:
    State state = STAND_BY_STATE;
    SrcType srcType;
    uint8_t pause = Pause::RESUME;
    uint8_t manualPause = Pause::RESUME;
    uint8_t srcVol;
    uint8_t switchPos;
    uint8_t refluxRatio;
    uint8_t heatPwr;
    uint8_t heatAdj;
    uint8_t hydroLvl;
    uint16_t alcLvl;
    uint16_t condMtrPos;
    uint16_t condMtrAdj;
    uint16_t outMtrPos;
    uint16_t retMtrPos;
    uint16_t condMtrCurPos;
    uint16_t outMtrCurPos;
    uint16_t retMtrCurPos;
    uint16_t swMtrCurPos;
    uint16_t extAdj;
    float steamTemp;
    float condTemp;
    float pipeTemp;
    float envTemp;
    float calcTemp;
    float pressure;
    uint16_t headOutML;
    uint32_t bodyOutML;
    uint32_t usedWaterML;
    uint32_t usedPowerW;
    unsigned long startTime;
    unsigned long elapsedTime;
    uint32_t name;

  public:
    IMSession();
    IMSession(uint32_t name, unsigned long startTime, SrcType type, uint8_t vol);

    uint32_t getName();
    SrcType getSrcType();
    uint8_t getSrcVol();
    State getState();
    uint8_t isPaused();
    bool isActive();
    uint8_t getSwitchPos();
    uint8_t getRefluxRatio();
    uint8_t getHeatPwr();
    uint8_t getHeatAdj();
    uint8_t getHydroLvl();
    uint16_t getAlcLvl();
    uint16_t getCondMtrPos();
    uint16_t getCondMtrAdj();
    uint16_t getOutMtrPos();
    uint16_t getRetMtrPos();
    uint16_t getCondMtrCurPos();
    uint16_t getOutMtrCurPos();
    uint16_t getRetMtrCurPos();
    uint16_t getSwMtrCurPos();
    uint16_t getExtAdj();
    float getSteamTemp();
    float getCondTemp();
    float getPipeTemp();
    float getEnvTemp();
    float getCalcTemp();
    float getPressure();
    uint16_t getHeadOutML();
    uint32_t getBodyOutML();
    uint32_t getUsedWaterML();
    uint32_t getUsedPowerW();
    unsigned long getStartTime();
    unsigned long getElapsedTime();

    void setName(uint32_t);
    void setSrcVol(uint8_t);
    void setSrcType(SrcType);
    void setState(State);
    void setPause(uint8_t);
    void setManualPause(uint8_t);
    void setSwitchPos(uint8_t);
    void setRefluxRatio(uint8_t);
    void setHeatPwr(uint8_t);
    void setHeatAdj(uint8_t);
    void setHydroLvl(uint8_t);
    void setAlcLvl(uint16_t);
    void setCondMtrPos(uint16_t);
    void setCondMtrAdj(uint16_t);
    void setOutMtrPos(uint16_t);
    void setRetMtrPos(uint16_t);
    void setCondMtrCurPos(uint16_t);
    void setOutMtrCurPos(uint16_t);
    void setRetMtrCurPos(uint16_t);
    void setSwMtrCurPos(uint16_t);
    void setExtAdj(uint16_t);
    void setSteamTemp(float);
    void setCondTemp(float);
    void setPipeTemp(float);
    void setEnvTemp(float);
    void setCalcTemp(float);
    void setPressure(float);
    void setHeadOutML(uint16_t);
    void setBodyOutML(uint32_t);
    void setUsedWaterML(uint32_t);
    void setUsedPowerW(uint32_t);
    void setStartTime(unsigned long);
    void setElapsedTime(unsigned long);

};

#endif