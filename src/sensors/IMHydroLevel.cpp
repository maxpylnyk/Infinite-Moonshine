#include "IMHydroLevel.h"

IMHydroLevel::IMHydroLevel() : IMSensor(syncBytesCount, initTime, requestTime, receiveTime) {}

void IMHydroLevel::setDataLo(int data) {
  dataLo = data;
}

int IMHydroLevel::getDataLo() {
  return dataLo;
}

void IMHydroLevel::setDataHi(int data) {
  dataHi = data;
}

int IMHydroLevel::getDataHi() {
  return dataHi;
}

void IMHydroLevel::setDataOver(int data) {
  dataOver = data;
}

int IMHydroLevel::getDataOver() {
  return dataOver;
}

bool IMHydroLevel::loReached() {
  return getDataLo() > treshold;
}

bool IMHydroLevel::hiReached() {
  return getDataHi() > treshold;
}

bool IMHydroLevel::overReached() {
  return getDataOver() > treshold;
}

void IMHydroLevel::setLevel(IMLevel value) {
  level = value;
}

bool IMHydroLevel::init() {
  return true;
}

void IMHydroLevel::debug() {
  receiveData();
  int Vin = 5;
  float VoutLo = 0;
  float VoutHi = 0;
  float VoutOver = 0;
  float buffer;
  float RLo = 0;
  float RHi = 0;
  float ROver = 0;

  Serial.println("Raw data "+String(getDataLo())+" "+String(getDataHi())+" "+String(getDataOver()));

  VoutLo = (getDataLo() * Vin) / 1024.0;
  VoutHi = (getDataHi() * Vin) / 1024.0;
  VoutOver = (getDataOver() * Vin) / 1024.0;
  Serial.println("Vout "+String(VoutLo)+" "+String(VoutHi)+" "+String(VoutOver));

  buffer = Vin / VoutLo - 1;
    RLo = refResistorLo * buffer;

  buffer = Vin / VoutHi - 1;
  RHi = refResistorHi * buffer;

  buffer = Vin / VoutOver - 1;
  ROver = refResistorOver * buffer;
  Serial.println("Resistance "+String(RLo)+" "+String(RHi)+" "+String(ROver));
}

void IMHydroLevel::requestData() {
  setMeasuring(true);
}

void IMHydroLevel::receiveData() {
  digitalWrite(OUT_PIN, HIGH);
  setDataLo(analogRead(LO_PIN));
  setDataHi(analogRead(HI_PIN));
  setDataOver(analogRead(OVR_PIN));
  digitalWrite(OUT_PIN, LOW);
  setMeasuring(false);
}

void IMHydroLevel::getSyncArray(uint8_t bytes[]) {
  bytes[0] = (uint8_t) getLevel();
}

void IMHydroLevel::sync(uint8_t bytes[]) {}

IMLevel IMHydroLevel::getLevel() {
  if (overReached()) {
    return OVR;
  }
  if (hiReached()) {
    return HI;
  }
  if (loReached()) {
    return OK;
  }
  return LO;
}

bool IMHydroLevel::isOverflowing() {
  return overReached();
}