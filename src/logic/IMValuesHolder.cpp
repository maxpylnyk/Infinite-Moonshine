#include "IMValuesHolder.h"

IMValuesHolder::IMValuesHolder(IMCondenserNode * condNode, IMExtractionNode * extNode,
  IMSwitchNode * swNode, IMThermometers * trm) : condNode(condNode), extNode(extNode),
  swNode(swNode), trm(trm) {}

bool IMValuesHolder::collectValues(bool useAlcMeter) {
  bool result = true;

  if (!DISABLE_ALC_METER) {
    if (!swNode->getAlc()->init()) {
      errors->add(IMError::NO_ALC);
    }
    if (useAlcMeter) {
      result &= swNode->getAlc()->collectReadings();
    }
  }
  result &= trm->collectReadings();
  result &= extNode->getBar()->collectReadings();
  result &= extNode->getHydroLvl()->collectReadings();

  return result;
}

void IMValuesHolder::prepareToCollect(bool useAlcMeter) {
  if (useAlcMeter && !DISABLE_ALC_METER) {
    swNode->getAlc()->prepareToCollect();
  }
  trm->prepareToCollect();
  extNode->getBar()->prepareToCollect();
  extNode->getHydroLvl()->prepareToCollect();
}

void IMValuesHolder::setErrorList(IMErrors * e) {
  errors = e;
}

void IMValuesHolder::setSwitchPos(uint8_t value) {
  swNode->getSwitch()->setSwitchPos(value);
}

void IMValuesHolder::setRefluxRatio(uint8_t value) {
  extNode->setRefluxRatio(value);
}

void IMValuesHolder::setHeatPwr(uint8_t value) {
  extNode->getHeater()->setPower(value);
}

void IMValuesHolder::setHeatAdj(uint8_t value) {
  extNode->getHeater()->setAdjStep(value);
}

void IMValuesHolder::setCondMtrPos(int16_t ml) {
  condNode->getMtr()->setTargetPosition(condNode->mlToSteps(ml));
}

void IMValuesHolder::setCondMtrAdj(int16_t value) {
  condNode->setAdj(value);
}

void IMValuesHolder::setOutMtrPos(int16_t ml) {
  extNode->getOutMtr()->setTargetPosition(extNode->mlToSteps(ml));
}

void IMValuesHolder::setRetMtrPos(int16_t ml) {
  extNode->getRetMtr()->setTargetPosition(extNode->mlToSteps(ml));
}

void IMValuesHolder::setExtAdj(int16_t value) {
  extNode->setAdj(value);
}

void IMValuesHolder::setCondCurPos(int16_t value) {
  condNode->getMtr()->setCurrentPosition(value);
}

void IMValuesHolder::setOutCurPos(int16_t value) {
  extNode->getOutMtr()->setCurrentPosition(value);
}

void IMValuesHolder::setRetCurPos(int16_t value) {
  extNode->getRetMtr()->setCurrentPosition(value);
}

void IMValuesHolder::setSwCurPos(int16_t value) {
  swNode->getSwitch()->setCurrentPos(value);
}

uint8_t IMValuesHolder::getSwitchPos() {
  return swNode->getSwitch()->getSwitchPos();
}

uint8_t IMValuesHolder::getRefluxRatio() {
  return extNode->getRefluxRatio();
}

uint8_t IMValuesHolder::getHeatPwr() {
  return extNode->getHeater()->getPower();
}

uint8_t IMValuesHolder::getHeatAdj() {
  return extNode->getHeater()->getAdjStep();
}

IMLevel IMValuesHolder::getHydroLvl() {
  return extNode->getHydroLvl()->getLevel();
}

uint16_t IMValuesHolder::getAlcLvl() {
  if (DISABLE_ALC_METER) {
    return 0;
  }
  return swNode->getAlc()->getLevel();
}

int16_t IMValuesHolder::getCondMtrPos() {
  return condNode->getMtr()->getTargetPosition();
}

int16_t IMValuesHolder::getCondMtrAdj() {
  return condNode->getAdj();
}

int16_t IMValuesHolder::getOutMtrPos() {
  return extNode->getOutMtr()->getTargetPosition();
}

int16_t IMValuesHolder::getRetMtrPos() {
  return extNode->getRetMtr()->getTargetPosition();
}

int16_t IMValuesHolder::getExtAdj() {
  return extNode->getAdj();
}

float IMValuesHolder::getSteamTemp() {
  return extNode->getSteamTrm()->getTemperature();
}

float IMValuesHolder::getCondTemp() {
  return condNode->getCondTrm()->getTemperature();
}

float IMValuesHolder::getPipeTemp() {
  return extNode->getPipeTrm()->getTemperature();
}

float IMValuesHolder::getEnvTemp() {
  return extNode->getEnvTrm()->getTemperature();
}

float IMValuesHolder::getCalcTemp() {
  return extNode->getCalcTemp();
}

float IMValuesHolder::getPressure() {
  return extNode->getBar()->getPressure();
}

int16_t IMValuesHolder::getCondCurPos() {
  return condNode->stepsToMl(condNode->getMtr()->getCurrentPosition());
}

int16_t IMValuesHolder::getOutCurPos() {
  return extNode->stepsToMl(extNode->getOutMtr()->getCurrentPosition());
}

int16_t IMValuesHolder::getRetCurPos() {
  return extNode->stepsToMl(extNode->getRetMtr()->getCurrentPosition());
}

int16_t IMValuesHolder::getSwCurPos() {
  return swNode->getMtr()->getCurrentPosition();
}

int16_t IMValuesHolder::getSwMtrPos() {
  return swNode->getMtr()->getTargetPosition();
}
