#ifndef IM_MEGA_H
#define IM_MEGA_H

#include "InfiniteMoonshine.h"
#include "logic/IMCondenserNode.h"
#include "logic/IMExtractionNode.h"
#include "logic/IMSwitchNode.h"
#include "graphics/IMUI.h"
//#include "utilities/IMLogger.h"
#include "utilities/IMValuesHolder.h"

class IMMega : public InfiniteMoonshine {
  private:
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

    IMCondenserNode condNode = IMCondenserNode(&trm, &condMtr);
    IMExtractionNode extNode = IMExtractionNode(&hlvl, &bar, &trm, &heater, &outMtr, &retMtr);
    IMSwitchNode swNode = IMSwitchNode(&alc, &swMtr);
    IMValuesHolder host = IMValuesHolder(&condNode, &extNode, &swNode, &trm);
    
    IMUI ui = IMUI(locale, &captions, &timer, &host);
    //IMLogger log = IMLogger();

    void setMasterSPI();
    void sendData();
    void receiveData();
    void showErrors();
    bool handleErrors();
    void moveMotors();

  public:
    IMMega();

    bool init();
    void loop();
    void debug();
    void receiveCallsign();

};

#endif
