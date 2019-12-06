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

uint16_t IMSession::getExtMtrAdj() {
  return extMtrAdj;
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

uint16_t IMSession::getHeadsOutML() {
  return headsOutML;
}

uint32_t IMSession::getEthanolOutML() {
  return ethanolOutML;
}

uint32_t IMSession::getConsumedWaterML() {
  return consumedWaterML;
}

uint32_t IMSession::getConsumedPowerW() {
  return consumedPowerW;
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

void IMSession::setExtMtrAdj(uint16_t value) {
  extMtrAdj = value;
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

void IMSession::setHeadsOutML(uint16_t value) {
  headsOutML = value;
}

void IMSession::setEthanolOutML(uint32_t value) {
  ethanolOutML = value;
}

void IMSession::setConsumedWaterML(uint32_t value) {
  consumedWaterML = value;
}

void IMSession::setConsumedPowerW(uint32_t value) {
  consumedPowerW = value;
}

void IMSession::setStartTime(unsigned long value) {
  startTime = value;
}

void IMSession::setElapsedTime(unsigned long value) {
  elapsedTime = value;
}
