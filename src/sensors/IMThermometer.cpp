#include "IMThermometer.h"

IMThermometer::IMThermometer() {}

void IMThermometer::setAddress(uint8_t * value) {
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

uint8_t * IMThermometer::getAddress() {
  return address;
}
