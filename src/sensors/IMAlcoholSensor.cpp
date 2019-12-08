#include "IMAlcoholSensor.h"

IMAlcoholSensor::IMAlcoholSensor() :
 IMSensor(initTime, requestTime, receiveTime, ALC_TIMEOUT) {
   pinMode(ALC_HEAT_PIN, OUTPUT);
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
  /*
  digitalWrite(ALC_HEAT_PIN, HIGH);

  for (int i = 1; i <= 60; i++) {
    Serial.print(analogRead(ALC_DATA_PIN));
    Serial.println(" "+String(i)+" s");
    delay(1000);
  }
  Serial.println("5 sec break");
  Serial.println();
  digitalWrite(ALC_HEAT_PIN, LOW);
  delay(5000);
  */
}

bool IMAlcoholSensor::ethanolDetected() {
  return getLevel() > treshold;
}

int16_t IMAlcoholSensor::getLevel() {
  return level;
}

void IMAlcoholSensor::requestData() {
  setMeasuring(true);
  setMeasured(false);
  digitalWrite(ALC_HEAT_PIN, HIGH);
}
void IMAlcoholSensor::receiveData() {
  setLevel(analogRead(ALC_DATA_PIN));
  digitalWrite(ALC_HEAT_PIN, LOW);
  setMeasuring(false);
  setMeasured(true);
}
