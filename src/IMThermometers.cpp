#include "IMThermometers.h"

IMThermometers::IMThermometers() : IMSensor(syncBytesCount, requestTime, receiveTime) {}

bool IMThermometers::initThermometer(IMThermometer& therm, DeviceAddress address, float adjustment) {
  bool online;

  therm.setAddress(address);
  therm.setAdjustment(adjustment);
  online = tempSensors.isConnected(address);
  if (online) {
    tempSensors.setResolution(address, resolution);
  }
  return online;
}

bool IMThermometers::init() {
  bool sensorsReady = true;

  tempSensors.begin();
  sensorOnline = initThermometer(steamTherm, t1Address, t1Adj);

  if (!initThermometer(steamTherm, t1Address, t1Adj);) {
    //log steam thermometer offline
    sensorsReady = false;
  }
  if (!initThermometer(condTherm, t2Address, t2Adj)) {
    //log condenser thermometer offline
    sensorsReady = false;
  }
  if (!initThermometer(pipeTherm, t3Address, t3Adj)) {
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
  steamTherm.setRawTemp(tempSensors.getTempC(steamTherm.getAddress()));
  condTherm.setRawTemp(tempSensors.getTempC(condTherm.getAddress()));
  pipeTherm.setRawTemp(tempSensors.getTempC(pipeTherm.getAddress()));
  setMeasuring(false);
}

uint8_t[] IMThermometers::getSyncArray() {
  int index = 0;
  uint8_t[syncBytesCount] data;
  uint8_t[] temp = toArray(getSteamTemp());

  for (; index < floatSize; index++) {
    data[index] = temp[index];
  }
  temp = toArray(getCondTemp());

  for (int i = 0; i < floatSize; i++, index++) {
    data[index] = temp[i];
  }
  temp = toArray(getPipeTemp());

  for (int i = 0; i < floatSize; i++, index++) {
    data[index] = temp[i];
  }
  return data;
}

void IMThermometers::sync(uint8_t[] array) {}

float IMThermometers::getSteamTemp() {
  return steamTherm.getTemperature();
}

float IMThermometers::getCondTemp() {
  return condTherm.getTemperature();
}

float IMThermometers::getPipeTemp() {
  return pipeTherm.getTemperature();
}
