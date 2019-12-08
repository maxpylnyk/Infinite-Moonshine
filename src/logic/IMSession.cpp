#include "IMSession.h"

IMSession::IMSession() : name(0), srcType(0), srcVol(0) {}

IMSession::IMSession(uint32_t name, unsigned long startTime, SrcType srcType, uint8_t srcVol) :
  name(name), startTime(startTime), srcType(srcType), srcVol(srcVol) {}

uint32_t IMSession::getName() {
  return name;
}

SrcType IMSession::getSrcType() {
  return srcType;
}

uint8_t IMSession::getSrcVol() {
  return srcVol;
}

State IMSession::getState() {
  return state;
}

bool IMSession::isActive() {
  return (int8_t)state > 0;
}

uint8_t IMSession::getSwitchPos() {
  return switchPos;
}

uint8_t IMSession::getRefluxRatio() {
  return refluxRatio;
}

uint8_t IMSession::getHeatPwr() {
  return heatPwr;
}

uint8_t IMSession::getHeatAdj() {
  return heatAdj;
}

uint8_t IMSession::getHydroLvl() {
  return hydroLvl;
}

uint16_t IMSession::getAlcLvl() {
  return alcLvl;
}

uint16_t IMSession::getCondMtrPos() {
  return condMtrPos;
}

uint16_t IMSession::getCondMtrAdj() {
  return condMtrAdj;
}

uint16_t IMSession::getOutMtrPos() {
  return outMtrPos;
}

uint16_t IMSession::getRetMtrPos() {
  return retMtrPos;
}

uint16_t IMSession::getCondMtrCurPos() {
  return condMtrCurPos;
}

uint16_t IMSession::getOutMtrCurPos() {
  return outMtrCurPos;
}

uint16_t IMSession::getRetMtrCurPos() {
  return retMtrCurPos;
}

uint16_t IMSession::getSwMtrCurPos() {
  return swMtrCurPos;
}

uint16_t IMSession::getExtAdj() {
  return extAdj;
}

float IMSession::getSteamTemp() {
  return steamTemp;
}

float IMSession::getCondTemp() {
  return condTemp;
}

float IMSession::getPipeTemp() {
  return pipeTemp;
}

float IMSession::getEnvTemp() {
  return envTemp;
}

float IMSession::getCalcTemp() {
  return calcTemp;
}

float IMSession::getPressure() {
  return pressure;
}

uint16_t IMSession::getHeadOutML() {
  return headOutML;
}

uint32_t IMSession::getBodyOutML() {
  return bodyOutML;
}

uint32_t IMSession::getUsedWaterML() {
  return usedWaterML;
}

uint32_t IMSession::getUsedPowerW() {
  return usedPowerW;
}

unsigned long IMSession::getStartTime() {
  return startTime;
}

unsigned long IMSession::getElapsedTime() {
  return elapsedTime;
}

void IMSession::setName(uint32_t value) {
  name = value;
}

uint8_t IMSession::isPaused() {
  if (MANUAL_MODE) {
    if (manualPause) {
      return manualPause;
    }
  }
  return pause;
}

void IMSession::setPause(uint8_t value) {
    pause = value;
}

void IMSession::setManualPause(uint8_t value) {
  if (MANUAL_MODE) {
    manualPause = value;
  }
}

void IMSession::setSrcVol(uint8_t value) {
  srcVol = value;
}

void IMSession::setSrcType(SrcType value) {
  srcType = value;
}

void IMSession::setState(State value) {
  state = value;
}

void IMSession::setSwitchPos(uint8_t value) {
  switchPos = value;
}

void IMSession::setRefluxRatio(uint8_t value) {
  refluxRatio = value;
}

void IMSession::setHeatPwr(uint8_t value) {
  heatPwr = value;
}

void IMSession::setHeatAdj(uint8_t value) {
  heatAdj = value;
}

void IMSession::setHydroLvl(uint8_t value) {
  hydroLvl = value;
}

void IMSession::setAlcLvl(uint16_t value) {
  alcLvl = value;
}

void IMSession::setCondMtrPos(uint16_t value) {
  condMtrPos = value;
}

void IMSession::setCondMtrAdj(uint16_t value) {
  condMtrAdj = value;
}

void IMSession::setOutMtrPos(uint16_t value) {
  outMtrPos = value;
}

void IMSession::setRetMtrPos(uint16_t value) {
  retMtrPos = value;
}

void IMSession::setCondMtrCurPos(uint16_t value) {
  condMtrCurPos = value;
}

void IMSession::setOutMtrCurPos(uint16_t value) {
  outMtrCurPos = value;
}

void IMSession::setRetMtrCurPos(uint16_t value) {
  retMtrCurPos = value;
}

void IMSession::setSwMtrCurPos(uint16_t value) {
  swMtrCurPos = value;
}

void IMSession::setExtAdj(uint16_t value) {
  extAdj = value;
}

void IMSession::setSteamTemp(float value) {
  steamTemp = value;
}

void IMSession::setCondTemp(float value) {
  condTemp = value;
}

void IMSession::setPipeTemp(float value) {
  pipeTemp = value;
}

void IMSession::setEnvTemp(float value) {
  envTemp = value;
}

void IMSession::setCalcTemp(float value) {
  calcTemp = value;
}

void IMSession::setPressure(float value) {
  pressure = value;
}

void IMSession::setHeadOutML(uint16_t value) {
  headOutML = value;
}

void IMSession::setBodyOutML(uint32_t value) {
  bodyOutML = value;
}

void IMSession::setUsedWaterML(uint32_t value) {
  usedWaterML = value;
}

void IMSession::setUsedPowerW(uint32_t value) {
  usedPowerW = value;
}

void IMSession::setStartTime(unsigned long value) {
  startTime = value;
}

void IMSession::setElapsedTime(unsigned long value) {
  elapsedTime = value;
}
