#ifndef INFINITE_MOONSHINE_H
#define INFINITE_MOONSHINE_H

#include "Arduino.h"
#include "stdint.h"
#include "logic/IMStates.h"
#include "utilities/IMTimer.h"
//#include "control/IMHeater.h"
//#include "sensors/IMHydroLevel.h"
//#include "sensors/IMBarometer.h"
//#include "sensors/IMAlcoholSensor.h"
//#include "sensors/IMThermometers.h"
//#include "control/IMStepMotor.h"

#define DEBUG_MODE 1

class InfiniteMoonshine {
  protected:
    static const uint8_t onlineMask    = 0x01;
    static const uint8_t transferMask  = 0x02;
    static const uint8_t restartMask   = 0x04;
    static const uint8_t initMask      = 0x08;

    static const uint8_t statusMask    = 0x0F;
    static const uint8_t logicMask     = 0xF0;

    static const int8_t dataArraySize = 44;

    static const int8_t interruptStartIndex = 0;
    static const int8_t interruptEndIndex = 1;

    static const int restartDelay = 10;
    static const int attemptsLimit = 3;

    bool initialize = true;
    volatile bool dataFromMaster = false;
    volatile bool dataFromSlave = false;
    volatile bool thisRestarted = false;
    volatile bool otherRestarted = false;

    bool dataTransfer = false;

    int connectionAttempts = 0;
    uint32_t sessionNum;
    IMTimer timer = IMTimer();

    volatile uint8_t dataIndex = 0;
    volatile uint8_t data[dataArraySize];

    bool readCallsign(uint8_t);
    uint8_t getCallsign();

    StateIndex getIndex(uint8_t);
    void clearArray();

  public:
    InfiniteMoonshine();

    bool init();
    void loop();
    void debug();

};

#endif
