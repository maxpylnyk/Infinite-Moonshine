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
    int16_t waterSpeed;
    int16_t waterAdj;
    int16_t extSpeed;
    int16_t refluxSpeed;
    int16_t extAdj;
    float steamTemp;
    float condTemp;
    float pipeTemp;
    float envTemp;
    float calcTemp;
    float pressure;
    uint16_t headOutML;
    uint32_t bodyOutML;
    float usedWaterL;
    float usedPowerKW;
    unsigned long startTime;
    unsigned long elapsedTime;
    uint32_t name;

  public:
    IMSession();
    IMSession(uint32_t name, unsigned long startTime, SrcType type, uint8_t vol);

    bool inHeadState();
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
    int16_t getWaterSpeed();
    int16_t getWaterAdj();
    int16_t getExtSpeed();
    int16_t getRefluxSpeed();
    int16_t getExtAdj();
    float getSteamTemp();
    float getCondTemp();
    float getPipeTemp();
    float getEnvTemp();
    float getCalcTemp();
    float getPressure();
    uint16_t getHeadOutML();
    uint32_t getBodyOutML();
    float getUsedWaterL();
    float getUsedPowerKW();
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
    void setWaterSpeed(int16_t);
    void setWaterAdj(int16_t);
    void setExtSpeed(int16_t);
    void setRefluxSpeed(int16_t);
    void setExtAdj(int16_t);
    void setSteamTemp(float);
    void setCondTemp(float);
    void setPipeTemp(float);
    void setEnvTemp(float);
    void setCalcTemp(float);
    void setPressure(float);
    void setHeadOutML(uint16_t);
    void setBodyOutML(uint32_t);
    void setUsedWaterL(float);
    void setUsedPowerKW(float);
    void setStartTime(unsigned long);
    void setElapsedTime(unsigned long);

};

#endif