#include "IMBarometer.h"

IMBarometer::IMBarometer() : IMSensor(initTime, requestTime, receiveTime, BAR_TIMEOUT) {}

void IMBarometer::setPressure(double value) {
  pressure = value;
}

bool IMBarometer::init() {
  return sensor.begin();
}

void IMBarometer::debug() {}

void IMBarometer::requestData() {
  setMeasuring(true);
  setMeasured(false);
  delay(sensor.startTemperature());
  sensor.getTemperature(t);
  delay(sensor.startPressure(resolution));
}

void IMBarometer::receiveData() {
  bool result = sensor.getPressure(p, t);
  setPressure(p * mmHgMultiplier);
  setMeasuring(false);
  setMeasured(result);
}

float IMBarometer::getPressure() {
  return pressure;
}