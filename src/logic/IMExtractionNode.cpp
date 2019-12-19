#include "IMExtractionNode.h" 

IMExtractionNode::IMExtractionNode(IMHydroLevel * hlvl, IMBarometer * bar,
     IMThermometers * trm, IMHeater * heater, IMStepMotor * outMtr, IMStepMotor * retMtr) :
     hlvl(hlvl), bar(bar), heater(heater), outMtr(outMtr), retMtr(retMtr) {
  steamTrm = trm->getSteamTrm();
  pipeTrm = trm->getPipeTrm();
  envTrm = trm->getEnvTrm();
}

IMHydroLevel * IMExtractionNode::getHydroLvl() {
  return hlvl;
}

IMHeater * IMExtractionNode::getHeater() {
  return heater;
}

IMStepMotor * IMExtractionNode::getOutMtr() {
  return outMtr;
}

IMStepMotor * IMExtractionNode::getRetMtr() {
  return retMtr;
}

IMBarometer * IMExtractionNode::getBar() {
  return bar;
}

IMThermometer * IMExtractionNode::getSteamTrm() {
  return steamTrm;
}

IMThermometer * IMExtractionNode::getPipeTrm() {
  return pipeTrm;
}

IMThermometer * IMExtractionNode::getEnvTrm() {
  return envTrm;
}

int16_t IMExtractionNode::getAdj() {
  return adj;
}

uint8_t IMExtractionNode::getRefluxRatio() {
  return refluxRatio;
}

float IMExtractionNode::getCalcTemp() {
  float temp = 0.038 * bar->getPressure() + 49.27;
  return temp;
}
  
void IMExtractionNode::setAdj(int16_t value) {
  adj = value;
}

void IMExtractionNode::setRefluxRatio(uint8_t value) {
  refluxRatio = value;
}

int IMExtractionNode::stepsToMl(int steps) {
  float ml = 0.0027 * steps * steps - 0.3846 * steps + 39.1;
  return (int) ml;
}

int IMExtractionNode::mlToSteps(int ml) {
  int steps = 0;

  while (ml > stepsToMl(steps)) {
    steps += 1;
  }
  return steps;
}
