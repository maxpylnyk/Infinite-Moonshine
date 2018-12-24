#include "IMThermometer.h"

IMThermometer::IMThermometer() {}

void IMThermometer::setAddress(DeviceAddress value) {
  address = value;
}

void IMThermometer::setAdjustment(float value) {
  adjustment = value;
}

void IMThermometer::setRawTemp(float value) {
  temperature = value + adjustment;
}

float IMThermometer::getTemperature() {
  return temperature;
}

DeviceAddress IMThermometer::getAddress() {
  return address;
}
