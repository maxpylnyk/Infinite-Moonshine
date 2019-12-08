#include "IMValuesHolder.h"

IMValuesHolder::IMValuesHolder(IMCondenserNode * condNode, IMExtractionNode * extNode,
  IMSwitchNode * swNode, IMThermometers * trm) : condNode(condNode), extNode(extNode),
  swNode(swNode), trm(trm) {}

bool IMValuesHolder::collectValues() {
  bool result = true;

  if (!DISABLE_ALC_METER) {
    result &= swNode->getAlc()->collectReadings();
  }
  result &= trm->collectReadings();
  result &= extNode->getBar()->collectReadings();
  result &= extNode->getHydroLvl()->collectReadings();

  return result;
}

void IMValuesHolder::prepareToCollect() {
  if (!DISABLE_ALC_METER) {
    swNode->getAlc()->prepareToCollect();
  }
  trm->prepareToCollect();
  extNode->getBar()->prepareToCollect();
  extNode->getHydroLvl()->prepareToCollect();
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

void IMValuesHolder::setCondMtrPos(uint16_t value) {
  condNode->getMtr()->setTargetPosition(value);
}

void IMValuesHolder::setCondMtrAdj(uint16_t value) {
  condNode->setAdj(value);
}

void IMValuesHolder::setOutMtrPos(uint16_t value) {
  extNode->getOutMtr()->setTargetPosition(value);
}

void IMValuesHolder::setRetMtrPos(uint16_t value) {
  extNode->getRetMtr()->setTargetPosition(value);
}

void IMValuesHolder::setExtAdj(uint16_t value) {
  extNode->setAdj(value);
}

void IMValuesHolder::setCondCurPos(uint16_t value) {
  condNode->getMtr()->setCurrentPosition(value);
}

void IMValuesHolder::setOutCurPos(uint16_t value) {
  extNode->getOutMtr()->setCurrentPosition(value);
}

void IMValuesHolder::setRetCurPos(uint16_t value) {
  extNode->getRetMtr()->setCurrentPosition(value);
}

void IMValuesHolder::setSwCurPos(uint16_t value) {
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

uint16_t IMValuesHolder::getCondMtrPos() {
  return condNode->getMtr()->getTargetPosition();
}

uint16_t IMValuesHolder::getCondMtrAdj() {
  return condNode->getAdj();
}

uint16_t IMValuesHolder::getOutMtrPos() {
  return extNode->getOutMtr()->getTargetPosition();
}

uint16_t IMValuesHolder::getRetMtrPos() {
  return extNode->getRetMtr()->getTargetPosition();
}

uint16_t IMValuesHolder::getExtAdj() {
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

uint16_t IMValuesHolder::getCondCurPos() {
  return condNode->getMtr()->getCurrentPosition();
}

uint16_t IMValuesHolder::getOutCurPos() {
  return extNode->getOutMtr()->getCurrentPosition();
}

uint16_t IMValuesHolder::getRetCurPos() {
  return extNode->getRetMtr()->getCurrentPosition();
}

uint16_t IMValuesHolder::getSwCurPos() {
  return swNode->getMtr()->getCurrentPosition();
}

uint16_t IMValuesHolder::getSwMtrPos() {
  return swNode->getMtr()->getTargetPosition();
}
