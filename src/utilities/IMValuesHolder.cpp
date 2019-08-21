#include "IMValuesHolder.h"

IMValuesHolder::IMValuesHolder(IMCondenserNode * condNode, IMExtractionNode * extNode,
  IMSwitchNode * swNode, IMThermometers * trm) : condNode(condNode), extNode(extNode),
  swNode(swNode), trm(trm) {}

bool IMValuesHolder::collectValues() {
  bool result = true;

  result &= swNode->getAlc()->collectReadings();
  result &= trm->collectReadings();
  result &= extNode->getBar()->collectReadings();
  result &= extNode->getHydroLvl()->collectReadings();

  return result;
}

void IMValuesHolder::prepareToCollect() {
  swNode->getAlc()->prepareToCollect();
  trm->prepareToCollect();
  extNode->getBar()->prepareToCollect();
  extNode->getHydroLvl()->prepareToCollect();
}

void IMValuesHolder::setSwitchPos(uint8_t value) {
  swNode->getSwitch()->setSwitchPos(value);
}

void IMValuesHolder::setHeatPwr(uint8_t value) {
  extNode->getHeater()->setPower(value);
}

void IMValuesHolder::setHeatAdj(uint8_t value) {
  extNode->getHeater()->setAdjStep(value);
}

void IMValuesHolder::setCondMtrPos(int16_t value) {
  condNode->getMtr()->setTargetPosition(value);
}

void IMValuesHolder::setCondMtrAdj(int16_t value) {
  condNode->setAdj(value);
}

void IMValuesHolder::setOutMtrPos(int16_t value) {
  extNode->getOutMtr()->setTargetPosition(value);
}

void IMValuesHolder::setRetMtrPos(int16_t value) {
  extNode->getRetMtr()->setTargetPosition(value);
}

void IMValuesHolder::setExtAdj(int16_t value) {
  extNode->setAdj(value);
}

void IMValuesHolder::setRefluxRatio(float value) {
  extNode->setRefluxRatio(value);
}

uint8_t IMValuesHolder::getSwitchPos() {
  return swNode->getSwitch()->getSwitchPos();
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
  return swNode->getAlc()->getLevel();
}

int16_t IMValuesHolder::getCondMtrPos() {
  return condNode->getMtr()->getCurrentPosition();
}

int16_t IMValuesHolder::getCondMtrAdj() {
  return condNode->getAdj();
}

int16_t IMValuesHolder::getOutMtrPos() {
  return extNode->getOutMtr()->getCurrentPosition();
}

int16_t IMValuesHolder::getRetMtrPos() {
  return extNode->getRetMtr()->getCurrentPosition();
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

float IMValuesHolder::getRefluxRatio() {
  return extNode->getRefluxRatio();
}