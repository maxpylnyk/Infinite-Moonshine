#include "IMAlcoholSensor.h"

IMAlcoholSensor::IMAlcoholSensor() :
 IMSensor(initTime, requestTime, receiveTime) {
   pinMode(PinMap::ALC_HEAT, OUTPUT);
 }

void IMAlcoholSensor::setLevel(int16_t data) {
  level = data;
}

bool IMAlcoholSensor::init() {
  requestData();
  delay(requestTime);
  receiveData();
  initLevel = getLevel();
  return initLevel < treshold;
}

void IMAlcoholSensor::debug() {
  digitalWrite(PinMap::ALC_HEAT, HIGH);

  for (int i = 1; i <= 60; i++) {
    Serial.print(analogRead(PinMap::ALC_DATA));
    Serial.println(" "+String(i)+" s");
    delay(1000);
  }
  Serial.println("5 sec break");
  Serial.println();
  digitalWrite(PinMap::ALC_HEAT, LOW);
  delay(5000);
}

bool IMAlcoholSensor::ethanolDetected() {
  return getLevel() > treshold;
}

int16_t IMAlcoholSensor::getLevel() {
  return level;
}

void IMAlcoholSensor::requestData() {
  setMeasuring(true);
  digitalWrite(PinMap::ALC_HEAT, HIGH);
}
void IMAlcoholSensor::receiveData() {
  setLevel(analogRead(PinMap::ALC_DATA));
  digitalWrite(PinMap::ALC_HEAT, LOW);
  setMeasuring(false);
}
