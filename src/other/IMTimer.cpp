#include "IMTimer.h"

IMTimer::IMTimer() {}

unsigned long IMTimer::start() {
  active = true;
  startTime = millis();
  checkTime = startTime;
  return startTime;
}

unsigned long IMTimer::check() {
  if (active) {
    prevTime = checkTime;
    checkTime = millis();
    return checkTime - prevTime;
  }
  return 0;
}

unsigned long IMTimer::getElapsedTime() {
  if (active) {
    return millis() - startTime;
  }
  return 0;
}

unsigned long IMTimer::stop() {
  if (active) {
    active = false;
    return millis() - startTime;
  }
  return 0;
}
