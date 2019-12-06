#ifndef IM_SESSION_H
#define IM_SESSION_H

#include "Arduino.h"
#include "stdint.h"
#include "utilities/IMCommons.h"

class IMSession {
  private:
    State state = STAND_BY_STATE;
    SrcType srcType;
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
    uint16_t extMtrAdj;
    float steamTemp;
    float condTemp;
    float pipeTemp;
    float envTemp;
    float calcTemp;
    float pressure;
    uint16_t headsOutML;
    uint32_t ethanolOutML;
    uint32_t consumedWaterML;
    uint32_t consumedPowerW;
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
    uint16_t getExtMtrAdj();
    float getSteamTemp();
    float getCondTemp();
    float getPipeTemp();
    float getEnvTemp();
    float getCalcTemp();
    float getPressure();
    uint16_t getHeadsOutML();
    uint32_t getEthanolOutML();
    uint32_t getConsumedWaterML();
    uint32_t getConsumedPowerW();
    unsigned long getStartTime();
    unsigned long getElapsedTime();

    void setName(uint32_t);
    void setState(State);
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
    void setExtMtrAdj(uint16_t);
    void setSteamTemp(float);
    void setCondTemp(float);
    void setPipeTemp(float);
    void setEnvTemp(float);
    void setCalcTemp(float);
    void setPressure(float);
    void setHeadsOutML(uint16_t);
    void setEthanolOutML(uint32_t);
    void setConsumedWaterML(uint32_t);
    void setConsumedPowerW(uint32_t);
    void setStartTime(unsigned long);
    void setElapsedTime(unsigned long);

};

#endif