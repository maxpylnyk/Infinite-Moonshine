#include "IMBarometer.h"

IMBarometer::IMBarometer() : IMSensor(initTime, requestTime, receiveTime, BAR_TIMEOUT) {}

void IMBarometer::setPressure(double value) {
  pressure = value;
}

void IMBarometer::setEnvTemp(double value) {
  envTemp = value;
}

bool IMBarometer::init() {
  return sensor.begin();
}

void IMBarometer::debug() {}

void IMBarometer::requestData() {
  setMeasuring(true);
  setMeasured(false);
  //delay(sensor.startTemperature());
  //sensor.getTemperature(envTemp);
  delay(sensor.startPressure(resolution));
}

void IMBarometer::receiveData() {
  setMeasured(sensor.getPressure(pressure, envTemp));
  setPressure(pressure * mmHgMultiplier);
  setMeasuring(false);
}

double IMBarometer::getPressure() {
  return pressure;
}