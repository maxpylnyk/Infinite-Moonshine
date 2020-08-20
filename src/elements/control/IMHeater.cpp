#include "elements/control/IMHeater.h"

IMHeater::IMHeater() {
  pinMode(SSR_PIN, OUTPUT);
}

void IMHeater::setPower(uint8_t value) {
  analogWrite(SSR_PIN, value);
  power = value;
}

uint8_t IMHeater::getPower() {
  return power;
}
