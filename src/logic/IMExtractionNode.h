#ifndef IM_EXTRACTION_NODE_H
#define IM_EXTRACTION_NODE_H

#include "utilities/IMConstants.h"
#include "sensors/IMHydroLevel.h"
#include "sensors/IMThermometers.h"
#include "sensors/IMBarometer.h"
#include "control/IMHeater.h"
#include "control/IMStepMotor.h"
#include "utilities/IMDecimal.h"

class IMExtractionNode {
  private:
    int16_t adj;
    uint8_t refluxRatio;
    IMHydroLevel * hlvl;
    IMHeater * heater;
    IMStepMotor * outMtr;
    IMStepMotor * retMtr;
    IMThermometer * steamTrm;
    IMThermometer * pipeTrm;
    IMThermometer * envTrm;
    IMBarometer * bar;

  public:
    IMExtractionNode(IMHydroLevel*, IMBarometer*,
     IMThermometers*, IMHeater*, IMStepMotor*, IMStepMotor*);

    IMHydroLevel * getHydroLvl();
    IMHeater * getHeater();
    IMStepMotor * getOutMtr();
    IMStepMotor * getRetMtr();
    IMBarometer * getBar();
    IMThermometer * getSteamTrm();
    IMThermometer * getPipeTrm();
    IMThermometer * getEnvTrm();
    int16_t getAdj();
    uint8_t getRefluxRatio();
    float getCalcTemp();
    int mlToSteps(int);
    int stepsToMl(int);

    void setAdj(int16_t);
    void setRefluxRatio(uint8_t);

};

#endif
