#ifndef IM_MEGA_H
#define IM_MEGA_H

#include "InfiniteMoonshine.h"
#include "sensors/IMAlcoholSensor.h"
#include "sensors/IMHydroLevel.h"
#include "sensors/IMThermometers.h"
#include "sensors/IMBarometer.h"
#include "control/IMHeater.h"
#include "control/IMStepMotor.h"
#include "graphics/IMUI.h"
#include "utilities/IMLogger.h"

class IMMega : public InfiniteMoonshine {
  private:
    float pressure;
    float envTemp;

    unsigned long temp;

    //IMState * state;
    Language locale = Language::RUSSIAN;
    IMCaptions captions = IMCaptions(locale);

    IMBarometer bar = IMBarometer();
    IMHydroLevel hlvl = IMHydroLevel();
    IMAlcoholSensor alc = IMAlcoholSensor();
    IMThermometers trm = IMThermometers();

    IMHeater heater = IMHeater();
    IMStepMotor outMtr = IMStepMotor(MTR1_1_PIN, MTR1_2_PIN, MTR1_3_PIN, MTR1_4_PIN);
    IMStepMotor retMtr = IMStepMotor(MTR2_1_PIN, MTR2_2_PIN, MTR2_3_PIN, MTR2_4_PIN);
    IMStepMotor condMtr = IMStepMotor(MTR3_1_PIN, MTR3_2_PIN, MTR3_3_PIN, MTR3_4_PIN);
    IMStepMotor swMtr = IMStepMotor(MTR4_1_PIN, MTR4_2_PIN, MTR4_3_PIN, MTR4_4_PIN);
    
    IMUI ui = IMUI(locale, &captions, &timer);
    //IMLogger log = IMLogger();

    void setMasterSPI();
    void sendData();
    void receiveData();

  public:
    IMMega();

    bool init();
    void loop();
    void debug();
    void receiveCallsign();
    void printErrors();
  /*
    String getState();
    IMLevel getHydroLevel();
    String getAlcLevel();
    String getSteamTemp();
    String getCondTemp();
    String getPipeTemp();
    String getEnvTemp();
    String getPressure();
    String getCondMtr();
    String getSwitch();
    String getHeat();
    String getOutMtr();
    String getRetMtr();
  */
};

#endif
