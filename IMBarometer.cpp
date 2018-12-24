#include "IMBarometer.h"

IMBarometer::IMBarometer() : IMSensor(syncBytesCount, requestTime, receiveTime) {}

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
  presSensor.startPressure(BAROMETER_RESOLUTION);
}

void IMBarometer::receiveData() {
  presSensor.getPressure(pressure, envTemp);
  setPres(pressure * mmHgMultiplier);
  setMeasuring(false);
}

uint8_t[] IMBarometer::getSyncArray() {
  int index = 0;
  uint8_t[syncBytesCount] data;
  uint8_t[] temp = toArray(getPres());

  for (; index < floatSize; index++) {
    data[index] = temp[index];
  }
  temp = toArray(getEnvTemp());

  for (int i = 0; index < syncBytesCount; i++, index++) {
    data[index] = temp[i];
  }
  return data;
}

void IMBarometer::sync(uint8_t[] array) {}

float IMBarometer::getPres() {
  return (float) pressure;
}

float IMBarometer::getEnvTemp() {
  return (float) envTemp;
}

float IMBarometer::getTableTemp() {
  return 0.038 * getPres() + 49.27;
}
