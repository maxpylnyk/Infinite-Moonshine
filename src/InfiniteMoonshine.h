#ifndef INFINITE_MOONSHINE_H
#define INFINITE_MOONSHINE_H

#include "Arduino.h"
#include "control/IMHeater.h"
#include "sensors/IMHydroLevel.h"
#include "sensors/IMBarometer.h"
#include "sensors/IMAlcoholSensor.h"
#include "sensors/IMThermometers.h"
#include "control/IMStepMotor.h"
#include "stdint.h"

class InfiniteMoonshine {
  private:
    bool dataFromMaster;
    bool dataFromSlave;
    bool restarted;

    uint32_t sessionNum;

  public:
    InfiniteMoonshine();

    void init();
    void loop();

    bool transferRequired();
    bool wasOffline();
    bool wasRestarted();

};

#endif
