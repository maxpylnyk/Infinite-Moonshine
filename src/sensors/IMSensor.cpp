#include "IMSensor.h"

IMSensor::IMSensor(int8_t arraySize, uint32_t initTime, uint32_t requestTime, uint32_t receiveTime) :
  IMSynchronizable(arraySize), initTime(initTime), requestTime(requestTime), receiveTime(receiveTime) {}

void IMSensor::setMeasuring(bool value) {
  measuring = value;
}

bool IMSensor::isMeasuring() {
  return measuring;
}

uint32_t IMSensor::getInitTime() {
  return initTime;
}

uint32_t IMSensor::getRequestTime() {
  return requestTime;
}

uint32_t IMSensor::getReceiveTime() {
  return receiveTime;
}

unsigned long IMSensor::getMeasuringTime() {
  unsigned long out = 0;

  out += getRequestTime();
  out += getReceiveTime();

  return out;
}
