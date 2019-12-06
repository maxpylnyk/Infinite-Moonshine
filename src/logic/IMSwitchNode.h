#ifndef IM_SWITCH_NODE_H
#define IM_SWITCH_NODE_H

#include "sensors/IMAlcoholSensor.h"
#include "control/IMStepMotor.h"
#include "control/IMSwitch.h"

class IMSwitchNode {
  private:
    IMAlcoholSensor * alc;
    IMStepMotor * swMtr;
    IMSwitch sw = IMSwitch();

  public:
    IMSwitchNode(IMAlcoholSensor*, IMStepMotor*);

    IMSwitch * getSwitch();
    IMAlcoholSensor * getAlc();
    void setMtrCurPos(uint16_t);

};

#endif
