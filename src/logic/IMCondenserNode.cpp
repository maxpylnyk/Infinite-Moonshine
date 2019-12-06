#include "IMCondenserNode.h"

IMCondenserNode::IMCondenserNode(IMThermometers * trm, IMStepMotor * mtr) {
  condTrm = trm->getCondTrm();
  envTrm = trm->getEnvTrm();
  condMtr = mtr;
}

int16_t IMCondenserNode::getAdj() {
  return adj;
}

IMStepMotor * IMCondenserNode::getMtr() {
  return condMtr;
}

IMThermometer * IMCondenserNode::getCondTrm() {
  return condTrm;
}

IMThermometer * IMCondenserNode::getEnvTrm() {
  return envTrm;
}

void IMCondenserNode::setAdj(int16_t value) {
  adj = value;
}

void IMCondenserNode::setMtrCurPos(uint16_t value) {
  condMtr->setCurrentPosition(value);
}
