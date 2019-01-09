#include "IMThermometers.h"

IMThermometers::IMThermometers() : IMSensor(syncBytesCount, initTime, requestTime, receiveTime) {}

bool IMThermometers::initThermometer(IMThermometer therm, uint8_t * address, float adjustment) {
  bool online;

  therm.setAddress(address);
  therm.setAdjustment(adjustment);
  tempSensors.setResolution(resolution);
  online = tempSensors.isConnected(address);

  return online;
}

bool IMThermometers::init() {
  bool sensorsReady = true;

  tempSensors.begin();

  if (!initThermometer(steamTherm, *t1Address, t1Adj)) {
    //log steam thermometer offline
    sensorsReady = false;
  }
  if (!initThermometer(condTherm, *t2Address, t2Adj)) {
    //log condenser thermometer offline
    sensorsReady = false;
  }
  if (!initThermometer(pipeTherm, *t3Address, t3Adj)) {
    //log pipe thermometer offline
    sensorsReady = false;
  }
  return sensorsReady;
}

void IMThermometers::debug() {
//valid address, check adjustments
}

void IMThermometers::requestData() {
  setMeasuring(true);
  tempSensors.requestTemperatures();
}

void IMThermometers::receiveData() {
  uint8_t * steamAddress = steamTherm.getAddress();
  uint8_t * condAddress = condTherm.getAddress();
  uint8_t * pipeAddress = pipeTherm.getAddress();

  steamTherm.setRawTemp(tempSensors.getTempC(steamAddress));
  condTherm.setRawTemp(tempSensors.getTempC(condAddress));
  pipeTherm.setRawTemp(tempSensors.getTempC(pipeAddress));
  setMeasuring(false);
}

void IMThermometers::getSyncArray(uint8_t bytes[]) {
  toArray(getSteamTemp(), *bytes);
  toArray(getCondTemp(), *(bytes+floatSize));
  toArray(getPipeTemp(), *(bytes+floatSize*2));
}

void IMThermometers::sync(uint8_t bytes[]) {}

float IMThermometers::getSteamTemp() {
  return steamTherm.getTemperature();
}

float IMThermometers::getCondTemp() {
  return condTherm.getTemperature();
}

float IMThermometers::getPipeTemp() {
  return pipeTherm.getTemperature();
}
