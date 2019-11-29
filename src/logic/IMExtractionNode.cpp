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

float IMExtractionNode::getRefluxRatio() {
  return refluxRatio;
}

float IMExtractionNode::getCalcTemp() {
  return 0.038 * bar->getPressure() + 49.27;
}
  
void IMExtractionNode::setAdj(int16_t value) {
  adj = value;
  //upd motors
}

void IMExtractionNode::setRefluxRatio(float value) {
  refluxRatio = value;
  //upd motors
}
