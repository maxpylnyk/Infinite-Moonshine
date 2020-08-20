#include "IMHardwareInterface.h"

IMHardwareInterface::IMHardwareInterface(IMHydroLevel * hlvl, 
  IMAlcoholSensor * alc, IMThermometers * trm, IMBarometer * bar, 
  IMHeater * heater, IMStepMotor * outMtr, IMStepMotor * retMtr, 
  IMStepMotor * condMtr, IMStepMotor * swMtr) : hlvl(hlvl), alc(alc), 
  trm(trm), bar(bar), heater(heater), outMtr(outMtr), retMtr(retMtr), 
  condMtr(condMtr), swMtr(swMtr) {}

bool IMHardwareInterface::collectValues(bool useAlcMeter) {
  bool result = true;

  if (!DISABLE_ALC_METER) {
    if (!alc->init()) {
      errors->add(IMError::NO_ALC);
    }
    if (useAlcMeter) {
      result &= alc->collectReadings();
    }
  }
  result &= trm->collectReadings();
  result &= bar->collectReadings();
  result &= hlvl->collectReadings();

  return result;
}

void IMHardwareInterface::prepareToCollect(bool useAlcMeter) {
  if (useAlcMeter && !DISABLE_ALC_METER) {
    alc->prepareToCollect();
  }
  trm->prepareToCollect();
  bar->prepareToCollect();
  hlvl->prepareToCollect();
}

void IMHardwareInterface::setErrorList(IMErrors * e) {
  errors = e;
}

uint8_t IMHardwareInterface::getHeat() {
  return heater->getPower();
}

IMLevel IMHardwareInterface::getHydroLvl() {
  return hlvl->getLevel();
}

uint16_t IMHardwareInterface::getAlcLvl() {
  if (DISABLE_ALC_METER) {
    return 0;
  }
  return alc->getLevel();
}

float IMHardwareInterface::getSteamTemp() {
  return trm->getSteamTrm()->getTemperature();
}

float IMHardwareInterface::getCondTemp() {
  return trm->getCondTrm()->getTemperature();
}

float IMHardwareInterface::getPipeTemp() {
  return trm->getPipeTrm()->getTemperature();
}

float IMHardwareInterface::getEnvTemp() {
  return trm->getEnvTrm()->getTemperature();
}

float IMHardwareInterface::getCalcTemp() {
  float temp = 0.038 * getPressure() + 49.27;
  return temp;
}

float IMHardwareInterface::getPressure() {
  return bar->getPressure();
}

void IMHardwareInterface::setHeat(uint8_t value) {
  heater->setPower(value);
}

void IMHardwareInterface::changeOutMtrPosOn(int32_t value) {
  outMtr->setTargetPosition(outMtr->getTargetPosition() + value);
}

void IMHardwareInterface::changeRetMtrPosOn(int32_t value) {
  retMtr->setTargetPosition(retMtr->getTargetPosition() + value);
}

void IMHardwareInterface::changeCondMtrPosOn(int32_t value) {
  condMtr->setTargetPosition(condMtr->getTargetPosition() + value);
}

void IMHardwareInterface::changeSwitchPosOn(int32_t value) {
  swMtr->setTargetPosition(swMtr->getTargetPosition() + value);
}

bool IMHardwareInterface::outMtrMoving() {
  return outMtr->isMoving();
}

bool IMHardwareInterface::retMtrMoving() {
  return retMtr->isMoving();
}

bool IMHardwareInterface::condMtrMoving() {
  return condMtr->isMoving();
}

bool IMHardwareInterface::swMtrMoving() {
  return swMtr->isMoving();
}
