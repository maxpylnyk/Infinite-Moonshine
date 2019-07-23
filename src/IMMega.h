#ifndef IM_MEGA_H
#define IM_MEGA_H

#include "InfiniteMoonshine.h"
#include "sensors/IMAlcoholSensor.h"
#include "sensors/IMHydroLevel.h"
#include "sensors/IMThermometers.h"
#include "sensors/IMBarometer.h"
#include "control/IMHeater.h"
#include "control/IMStepMotor.h"

class IMState;

class IMMega : public InfiniteMoonshine {
  private:
    float pressure;
    float envTemp;

    //IMState * state;
    Language locale = Language::RUSSIAN;
    IMCaptions captions = IMCaptions(locale);
    IMBarometer bar = IMBarometer();
    IMHydroLevel hlvl = IMHydroLevel();
    IMAlcoholSensor alc = IMAlcoholSensor();
    IMThermometers trm = IMThermometers();
    IMHeater heater = IMHeater();
    IMStepMotor outMtr = IMStepMotor(PinMap::MTR1_1, PinMap::MTR1_2, PinMap::MTR1_3, PinMap::MTR1_4);
    IMStepMotor retMtr = IMStepMotor(PinMap::MTR2_1, PinMap::MTR2_2, PinMap::MTR2_3, PinMap::MTR2_4);
    IMStepMotor condMtr = IMStepMotor(PinMap::MTR3_1, PinMap::MTR3_2, PinMap::MTR3_3, PinMap::MTR3_4);
    IMStepMotor swMtr = IMStepMotor(PinMap::MTR4_1, PinMap::MTR4_2, PinMap::MTR4_3, PinMap::MTR4_4);

    void sendData();
    void receiveData();

  public:
    IMMega();

    bool init();
    void loop();
    void debug();
    void receiveCallsign();
    void printErrors();

};

#endif
