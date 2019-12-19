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

int16_t IMCondenserNode::stepsToMl(int steps) {
  IMDecimal ml = IMDecimal(1.9236 * steps + 124.5);
  return ml.getInt();
}

int16_t IMCondenserNode::mlToSteps(int ml) {
  IMDecimal steps = IMDecimal(1.0 * (ml - 124) / 1.9236);
  return steps.getInt();
}

void IMCondenserNode::standBy() {
  getMtr()->zeroPosition();
}

void IMCondenserNode::cool() {
  maintainTemp(FLEGMA_TEMP);
}

void IMCondenserNode::maintainTemp(float target) {
  
  if (millis() - updTime < COND_INERTION || !getMtr()->onPosition()) {
    return;
  }
  float diff = target - getCondTrm()->getTemperature();

  if (diff > TEMP_OFFSET) {
    getMtr()->setTargetPosition(
      getMtr()->getCurrentPosition() - mlToSteps(getAdj())
    );
  } else if (diff < -1.0 * TEMP_OFFSET) {
    getMtr()->setTargetPosition(
      getMtr()->getCurrentPosition() + mlToSteps(getAdj())
    );
  }
  updTime = millis();
  
}
