#include "IMHydroLevel.h"

IMHydroLevel::IMHydroLevel() : IMSensor(initTime, requestTime, receiveTime, HLVL_TIMEOUT) {}

bool IMHydroLevel::init() {
  //test for false output?
  return true;
}

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

void IMHydroLevel::debug() {
  /*
  receiveData();
  int Vin = 5;
  float VoutLo = 0;
  float VoutHi = 0;
  float VoutOver = 0;
  float buffer;
  float RLo = 0;
  float RHi = 0;
  float ROver = 0;

  Serial.println("raw data "+String(getDataLo())+" "+String(getDataHi())+" "+String(getDataOver()));

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
  Serial.println("resistance "+String(RLo)+" "+String(RHi)+" "+String(ROver));
  Serial.println();
  delay(1000);
  */
}

void IMHydroLevel::requestData() {
  setMeasuring(true);
  setMeasured(false);
}

void IMHydroLevel::receiveData() {
  digitalWrite(HLVL_OUT_PIN, HIGH);
  setDataLo(analogRead(HLVL_LO_PIN));
  setDataHi(analogRead(HLVL_HI_PIN));
  setDataOver(analogRead(HLVL_OVR_PIN));
  digitalWrite(HLVL_OUT_PIN, LOW);
  setMeasuring(false);
  setMeasured(true);
}

IMLevel IMHydroLevel::getLevel() {
  //Serial.println("hlvl "+String(getDataLo())+" "+String(getDataHi())+" "+String(getDataOver()));
  if (overReached()) {
    return IMLevel::OVR;
  }
  if (hiReached()) {
    return IMLevel::HI;
  }
  if (loReached()) {
    return IMLevel::OK;
  }
  return IMLevel::LO;
}

bool IMHydroLevel::isOverflowing() {
  return overReached();
}
