#include "IMTimer.h"

IMTimer::IMTimer() {}

unsigned long IMTimer::start() {
  startTime = millis();
  checkTime = startTime;
  return startTime;
}

unsigned long IMTimer::check() {
  prevTime = checkTime;
  checkTime = millis();
  return checkTime - prevTime;
}

unsigned long IMTimer::stop() {
  return millis() - startTime;
}

String IMTimer::toString() {
  String timeStamp = "";


  return "YYYY.MM.DD hh:mm:ss";
}
