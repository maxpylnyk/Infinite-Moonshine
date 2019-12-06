#ifndef IM_CONDENSER_NODE_H
#define IM_CONDENSER_NODE_H

#include "utilities/IMCommons.h"
#include "sensors/IMThermometers.h"
#include "control/IMStepMotor.h"

class IMCondenserNode {
  private:
    int16_t adj;
    IMStepMotor * condMtr;
    IMThermometer * condTrm;
    IMThermometer * envTrm;

  public:
    IMCondenserNode(IMThermometers*, IMStepMotor*);

    int16_t getAdj();
    IMStepMotor * getMtr();
    IMThermometer * getCondTrm();
    IMThermometer * getEnvTrm();

    void setAdj(int16_t);
    void setMtrCurPos(uint16_t);
    
};

#endif
