#include "IMBarometer.h"

IMBarometer::IMBarometer() : IMSensor(syncBytesCount, initTime, requestTime, receiveTime) {}

void IMBarometer::setPres(float value) {
  pressure = value;
}

void IMBarometer::setEnvTemp(float value) {
  envTemp = value;
}

bool IMBarometer::init() {
  return presSensor.begin();
}

void IMBarometer::debug() {

}

void IMBarometer::requestData() {
  setMeasuring(true);
  delay(presSensor.startTemperature());
  presSensor.getTemperature(envTemp);
  presSensor.startPressure(resolution);
}

void IMBarometer::receiveData() {
  presSensor.getPressure(pressure, envTemp);
  setPres(pressure * mmHgMultiplier);
  setMeasuring(false);
}

void IMBarometer::getSyncArray(uint8_t bytes[]) {
  toArray(getPres(), *bytes);
  toArray(getEnvTemp(), *(bytes+floatSize));
}

void IMBarometer::sync(uint8_t bytes[]) {}

float IMBarometer::getPres() {
  return (float) pressure;
}

float IMBarometer::getEnvTemp() {
  return (float) envTemp;
}

float IMBarometer::getTableTemp() {
  return 0.038 * getPres() + 49.27;
}
