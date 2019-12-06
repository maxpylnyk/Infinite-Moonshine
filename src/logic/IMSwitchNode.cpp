#include "IMSwitchNode.h"

IMSwitchNode::IMSwitchNode(IMAlcoholSensor * sens, IMStepMotor * mtr) {
    alc = sens;
    swMtr = mtr;
    sw.setMotor(swMtr);
  }

IMSwitch * IMSwitchNode::getSwitch() {
  return &sw;
}

IMAlcoholSensor * IMSwitchNode::getAlc() {
  return alc;
}

void IMSwitchNode::setMtrCurPos(uint16_t value) {
  if (value) {
    swMtr->setCurrentPosition(BODY_POS);
  } else {
    swMtr->setCurrentPosition(HEAD_POS);
  }
  
}
