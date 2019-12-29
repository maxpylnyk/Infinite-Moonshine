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
  if (steps <= 378) {
    return 0;
  }
  IMDecimal ml = IMDecimal(0.0015 * steps * steps -0.287 * steps -104.24);
  return ml.getInt();
}

int16_t IMCondenserNode::mlToSteps(int ml) {
  int steps = 0;

  while (ml > stepsToMl(steps)) {
    steps += 1;
  }
  return steps;
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
