#include "IMThermometers.h"

IMThermometers::IMThermometers() : IMSensor(initTime, requestTime, receiveTime) {
  for (int8_t i = 0; i < thermometersCount; i++) {
    trms[i].setErrorList(errors);
  }
}

void IMThermometers::printAddress(const uint8_t * address) {
  for (uint8_t i = 0; i < 8; i++) {
    if (address[i] < 16) Serial.print("0");
    Serial.print(address[i], HEX);
  }
}

bool IMThermometers::init() {
  bool ready = true;
  sensors.begin();
  sensors.setResolution(resolution);
  
  for (int8_t i = 0; i < thermometersCount; i++) {
    ready &= trms[i].online();
  }
  return ready;
}

void IMThermometers::debug() {
  uint8_t deviceCount = sensors.getDeviceCount();
  DeviceAddress addr[deviceCount];

  Serial.println(String(deviceCount) + " thermometers online.");
  stopwatch.start();
  sensors.requestTemperatures();
  Serial.println("request time "+String(stopwatch.check())+" ms");

  for (int i = 0; i < deviceCount; i++) {
    sensors.getAddress(addr[i], i);
    Serial.print("trm "+String(i+1)+" addr ");
    printAddress(addr[i]);
    stopwatch.check();
    Serial.print(" value "+String(sensors.getTempC(addr[i]), DEC));
    Serial.println(" receive time "+String(stopwatch.check())+" ms");
  }
  Serial.println("overall measure time "+String(stopwatch.stop())+" ms");
  Serial.println();
}

void IMThermometers::setErrorList(IMErrors * list) {
  errors = list;
}

void IMThermometers::requestData() {
  setMeasuring(true);
  setMeasured(false);
  stopwatch.start();
  sensors.requestTemperatures();
}

void IMThermometers::receiveData() {
  bool result = true;

  result &= steamTrm.receiveData();
  result &= pipeTrm.receiveData();
  result &= condTrm.receiveData();
  result &= envTrm.receiveData();
  result &= stopwatch.stop() >= getMeasuringTime();

  setMeasuring(false);
  setMeasured(result);
}

float IMThermometers::getSteamTemp() {
  return steamTrm.getTemperature();
}

float IMThermometers::getPipeTemp() {
  return pipeTrm.getTemperature();
}

float IMThermometers::getCondTemp() {
  return condTrm.getTemperature();
}

float IMThermometers::getEnvTemp() {
  return envTrm.getTemperature();
}
