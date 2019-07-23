#include "IMThermometer.h"

IMThermometer::IMThermometer(DallasTemperature * sensors, 
  uint8_t * address, float adj, IMError error) {
  setSensors(sensors);
  setAddress(address);
  setAdjustment(adj);
  setError(error);
}

void IMThermometer::setAddress(uint8_t * value) {
  address = value;
}

void IMThermometer::setAdjustment(float value) {
  adjustment = value;
}

void IMThermometer::setRawTemp(float value) {
  temperature = value;

  if (value != DEVICE_DISCONNECTED_C) {
    temperature += adjustment;
  }
}

float IMThermometer::getTemperature() {
  return temperature;
}

uint8_t * IMThermometer::getAddress() {
  return address;
}

void IMThermometer::setMeasured(bool value) {
  measured = value;
}

void IMThermometer::setSensors(DallasTemperature * dt) {
  sensors = dt;
}

bool IMThermometer::dataReady() {
  return measured;
}

void IMThermometer::setError(IMError e) {
  error = e;
}

void IMThermometer::setErrorList(IMErrors * list) {
  errors = list;
}

bool IMThermometer::online() {
  bool connected = sensors->isConnected(getAddress());

  if (!connected) {
    errors->add(error);
  }
  return connected;
}

bool IMThermometer::receiveData() {
  bool ready = true;
  float value;

  if (sensors->isConnected(getAddress())) {
    value = sensors->getTempC(getAddress());
    setRawTemp(value);
    ready &= value != DEVICE_DISCONNECTED_C;
  } else {
    errors->add(error);
    ready = false;
  }
  setMeasured(ready);
  return ready;
}
