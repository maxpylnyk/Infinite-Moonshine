#include "IMSensor.h"

IMSensor::IMSensor(uint32_t initTime, uint32_t requestTime, 
  uint32_t receiveTime, unsigned long timeout) : initTime(initTime), 
  requestTime(requestTime), receiveTime(receiveTime), timeout(timeout) {}

void IMSensor::setMeasuring(bool value) {
  measuring = value;
}

bool IMSensor::isMeasuring() {
  return measuring;
}

void IMSensor::setMeasured(bool value) {
  measured = value;
}

bool IMSensor::dataReady() {
  return measured;
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

bool IMSensor::collectReadings() {
  if (millis() - lastMeasureTime >= timeout) {
    if (!isMeasuring()) {
      lastRequestTime = millis();
      requestData();
      return false;
    } else {
      if (millis() - lastRequestTime >= getRequestTime()) {
        receiveData();

        if (dataReady()) {
          lastMeasureTime = millis();
        } else {
          //error?
        }
        return dataReady();
      }
      return false;
    }
  }
  return dataReady();
}

void IMSensor::prepareToCollect() {
  setMeasured(false);
}
