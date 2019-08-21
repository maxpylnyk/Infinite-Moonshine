#ifndef IM_HEATER_H
#define IM_HEATER_H

#include "Arduino.h"
#include "stdint.h"
#include "utilities/IMCommons.h"
#include "InfiniteMoonshine.h"

typedef enum HeaterCall : int8_t {
  DECREASE = -1,
  FIXED    =  0,
  INCREASE =  1
};

class IMHeater {
  private:
    static const uint8_t powerOff = 0;
    static const uint8_t powerMax = 255;
    static const uint8_t minAdjStep = 1;
    static const uint8_t maxAdjStep = 128;
    static const int8_t maxCount = 3;
    static const int8_t adjCoef = 2;

    int8_t coarseCounter;
    int8_t fineCounter;
    HeaterCall prevCall;
    uint8_t adjStep;
    uint8_t power;

    bool tuneAdjStep();

  public:
    IMHeater();

    bool decreaseHeat();
    bool increaseHeat();
    void off();
    void maxValue();
    uint8_t getPower();
    uint8_t getAdjStep();
    void setInitPower(uint8_t);
    void setInitAdj(uint8_t);
    //public for debug and manual mode
    void setPower(uint8_t);
    bool setAdjStep(uint8_t);

};

#endif
