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

IMStepMotor * IMSwitchNode::getMtr() {
  return swMtr;
}
