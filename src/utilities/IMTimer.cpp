#include "IMTimer.h"

IMTimer::IMTimer() {
  clock.begin();
}

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
