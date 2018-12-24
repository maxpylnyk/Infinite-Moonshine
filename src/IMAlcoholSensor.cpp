#include "IMAlcoholSensor.h"

IMAlcoholSensor::IMAlcoholSensor() :
 IMSensor(syncBytesCount, initTime, requestTime, receiveTime) {}

void IMAlcoholSensor::setValue(int16_t data) {
  value = data;
}

bool IMAlcoholSensor::init() {
  pinMode(HEAT_PIN, OUTPUT);
  return true;
}

void IMAlcoholSensor::debug() {

}

bool IMAlcoholSensor::ethanolDetected() {
  return getValue() > treshold;
}

int16_t IMAlcoholSensor::getValue() {
  return value;
}

void IMAlcoholSensor::getSyncArray(uint8_t bytes[]) {
  int16_t data = getValue();
  toArray(data, bytes);
}

void IMAlcoholSensor::sync(uint8_t bytes[]) {}

void IMAlcoholSensor::requestData() {
  setMeasuring(true);
  digitalWrite(HEAT_PIN, HIGH);
}
void IMAlcoholSensor::receiveData() {
  setValue(analogRead(DATA_PIN));
  digitalWrite(HEAT_PIN, LOW);
  setMeasuring(false);
}
