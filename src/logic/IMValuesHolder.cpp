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

void IMValuesHolder::setRefluxRatio(uint8_t value) {
  extNode->setRefluxRatio(value);
}

void IMValuesHolder::setHeatPwr(uint8_t value) {
  extNode->getHeater()->setPower(value);
}

void IMValuesHolder::setHeatAdj(uint8_t value) {
  extNode->getHeater()->setAdjStep(value);
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

int16_t IMValuesHolder::getWaterAdj() {
  return condNode->getAdj();
}

int16_t IMValuesHolder::getExtAdj() {
  return extNode->getAdj();
}

void IMValuesHolder::setWaterAdj(int16_t value) {
  condNode->setAdj(value);
}

void IMValuesHolder::setExtAdj(int16_t value) {
  extNode->setAdj(value);
}

bool IMValuesHolder::outMtrMoving() {
  return extNode->getOutMtr()->isMoving();
}

bool IMValuesHolder::retMtrMoving() {
  return extNode->getRetMtr()->isMoving();
}

bool IMValuesHolder::condMtrMoving() {
  return condNode->getMtr()->isMoving();
}

bool IMValuesHolder::swMtrMoving() {
  return swNode->getMtr()->isMoving();
}

uint8_t IMValuesHolder::getSwitchPos() {
  return swNode->getSwitch()->getSwitchPos();
}

int16_t IMValuesHolder::getSwitchSteps() {
  return swNode->getMtr()->getCurrentPosition();
}

int16_t IMValuesHolder::getSwitchTarget() {
  return swNode->getMtr()->getTargetPosition();
}

int16_t IMValuesHolder::getExtSpeed() {
  return extNode->stepsToMl(extNode->getOutMtr()->getCurrentPosition());
}

int16_t IMValuesHolder::getRefluxSpeed() {
  return extNode->stepsToMl(extNode->getRetMtr()->getCurrentPosition());
}

int16_t IMValuesHolder::getWaterSpeed() {
  return condNode->stepsToMl(condNode->getMtr()->getCurrentPosition());
}

void IMValuesHolder::setSwitchPos(uint8_t value) {
  swNode->getSwitch()->setSwitchPos(value);
}

void IMValuesHolder::setExtSpeed(int16_t ml) {
  if (ml < extNode->stepsToMl(0)) {
    ml = extNode->stepsToMl(0);
  }
  extNode->getOutMtr()->setTargetPosition(extNode->mlToSteps(ml));
}

void IMValuesHolder::setRefluxSpeed(int16_t ml) {
  if (ml < extNode->stepsToMl(0)) {
    ml = extNode->stepsToMl(0);
  }
  extNode->getRetMtr()->setTargetPosition(extNode->mlToSteps(ml));
}

void IMValuesHolder::setWaterSpeed(int16_t ml) {
  if (ml < condNode->stepsToMl(0)) {
    ml = condNode->stepsToMl(0);
  }
  condNode->getMtr()->setTargetPosition(condNode->mlToSteps(ml));
}

void IMValuesHolder::restoreSwitch(uint8_t pos) {
  swNode->getSwitch()->setCurrentPos(pos);
}

void IMValuesHolder::restoreExtSpeed(int16_t ml) {
  if (ml < extNode->stepsToMl(0)) {
    ml = extNode->stepsToMl(0);
  }
  extNode->getOutMtr()->setCurrentPosition(extNode->mlToSteps(ml));
}

void IMValuesHolder::restoreRefluxSpeed(int16_t ml) {
  if (ml < extNode->stepsToMl(0)) {
    ml = extNode->stepsToMl(0);
  }
  extNode->getRetMtr()->setCurrentPosition(extNode->mlToSteps(ml));
}

void IMValuesHolder::restoreWaterSpeed(int16_t ml) {
  if (ml < condNode->stepsToMl(0)) {
    ml = condNode->stepsToMl(0);
  }
  condNode->getMtr()->setCurrentPosition(condNode->mlToSteps(ml));
}
