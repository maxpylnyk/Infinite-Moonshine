#ifndef INFINITE_MOONSHINE_H
#define INFINITE_MOONSHINE_H

#include "Arduino.h"
#include "IMHeater.h"
#include "IMHydroLevel.h"
#include "IMBarometer.h"
#include "IMAlcoholSensor.h"
#include "IMThermometers.h"
#include "IMStepMotor.h"
#include "IMSwitch.h"
#include "stdint.h"

class InfiniteMoonshine {
  private:
    bool dataFromMaster;
    bool dataFromSlave;
    bool wasRestarted;

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
