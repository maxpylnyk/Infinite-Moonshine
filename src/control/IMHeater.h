#ifndef IM_HEATER_H
#define IM_HEATER_H

#include "Arduino.h"
#include "stdint.h"
#include "utilities/IMSynchronizable.h"

#define SSR_PIN 3

typedef enum {
  DECREASE = -1,
  FIXED    =  0,
  INCREASE =  1
} HeaterCall;

class IMHeater : public IMSynchronizable {
  private:
    static const int8_t syncBytesCount = byteSize + byteSize;
    static const uint8_t powerOff = 0;
    static const uint8_t powerMin = 127;
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
    uint8_t powerHead;
    uint8_t powerBody;

    void setPower(uint8_t value);
    bool setAdjStep(uint8_t value);
    bool tuneAdjStep();

  public:
    IMHeater(uint8_t powerHead, uint8_t powerBody, uint8_t adjStep);

    bool decreaseHeat();
    bool increaseHeat();
    void off();
    void minBoilingValue();
    void headValue();
    void bodyValue();
    void maxValue();
    uint8_t getPower();
    uint8_t getAdjStep();

    void getSyncArray(uint8_t bytes[]);
    void sync(uint8_t bytes[]);

};

#endif
