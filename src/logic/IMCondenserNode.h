#ifndef IM_CONDENSER_NODE_H
#define IM_CONDENSER_NODE_H

#include "utilities/IMConstants.h"
#include "sensors/IMThermometers.h"
#include "control/IMStepMotor.h"
#include "utilities/IMDecimal.h"

class IMCondenserNode {
  private:
    int16_t adj;
    IMStepMotor * condMtr;
    IMThermometer * condTrm;
    IMThermometer * envTrm;
    unsigned long updTime;

    void maintainTemp(float);

  public:
    IMCondenserNode(IMThermometers*, IMStepMotor*);

    int16_t getAdj();
    IMStepMotor * getMtr();
    IMThermometer * getCondTrm();
    IMThermometer * getEnvTrm();

    void setAdj(int16_t);
    int16_t mlToSteps(int);
    int16_t stepsToMl(int);
    void standBy();
    void cool();
    
};

#endif
