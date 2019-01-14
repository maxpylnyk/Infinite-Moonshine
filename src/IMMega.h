#ifndef IM_MEGA_H
#define IM_MEGA_H

#include "InfiniteMoonshine.h"
#include "sensors/IMAlcoholSensor.h"
#include "sensors/IMHydroLevel.h"
#include "sensors/IMThermometers.h"
#include "control/IMHeater.h"
#include "control/IMStepMotor.h"

class IMState;

class IMMega : public InfiniteMoonshine {
  private:
    static const uint8_t RST_PIN = 49;

    volatile bool interrupted;
    IMState * state;

    void initSlaveSPI();
    void initSlaveMode();
    void initInterrupts();

    bool readCallsign(uint8_t);
    uint8_t getCallsign();

    void restartMaster();

  public:
    IMMega();

    bool init();
    void loop();
    void debug();
    void interruptRoutine();

};

#endif
