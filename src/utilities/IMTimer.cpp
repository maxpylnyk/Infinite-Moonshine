#include "IMTimer.h"

IMTimer::IMTimer() {}

bool IMTimer::init() {
  return clock.begin();
}

void IMTimer::setupTime() {
  clock.setDateTime(__DATE__, __TIME__);
}

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

String IMTimer::getTime() {
  String out;

  dt = clock.getDateTime();
  out = String(dt.hour / 10) + String(dt.hour % 10);
  out += ":" + String(dt.minute / 10) + String(dt.minute % 10);

  return out;
}

String IMTimer::getDate() {
  String out;

  dt = clock.getDateTime();
  out = String(dt.day / 10) + String(dt.day % 10);
  out += "." + String(dt.month / 10) + String(dt.month % 10);
  out += "." + String(dt.year);

  return out;
}

String IMTimer::getLogStamp() {
  String out;

  dt = clock.getDateTime();
  out = String(dt.year);
  out += "-" + String(dt.month / 10) + String(dt.month % 10);
  out += "-" + String(dt.day / 10) + String(dt.day % 10);
  out += " " + String(dt.hour / 10) + String(dt.hour % 10);
  out += ":" + String(dt.minute / 10) + String(dt.minute % 10);
  out += ":" + String(dt.second / 10) + String(dt.second % 10);

  return out;
}

String IMTimer::getFileName() {
  String out;

  dt = clock.getDateTime();
  out = String(dt.year);
  out += String(dt.month / 10) + String(dt.month % 10);
  out += String(dt.day / 10) + String(dt.day % 10);
  out += String(extension);

  return out;
}

float IMTimer::getEnvTemp() {
  clock.forceConversion();
  return clock.readTemperature();
}
