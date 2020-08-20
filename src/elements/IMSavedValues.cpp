#include "IMSavedValues.h"

IMSavedValues::IMSavedValues() {}

bool IMSavedValues::useAlcMeter() {
  return alcMeterEnabled;
}

uint8_t IMSavedValues::getHeat() {
  return heat;
}

uint8_t IMSavedValues::getHydroLvl() {
  return hydroLvl;
}

uint16_t IMSavedValues::getAlcLvl() {
  return alcLvl;
}

float IMSavedValues::getSteamTemp() {
  return steamTemp;
}

float IMSavedValues::getCondTemp() {
  return condTemp;
}

float IMSavedValues::getPipeTemp() {
  return pipeTemp;
}

float IMSavedValues::getEnvTemp() {
  return envTemp;
}

float IMSavedValues::getPressure() {
  return pressure;
}

void IMSavedValues::enableAlcMeter(bool value) {
  alcMeterEnabled = value;
}

void IMSavedValues::setHeat(uint8_t value) {
  heat = value;
}

void IMSavedValues::setHydroLvl(uint8_t value) {
  hydroLvl = value;
}

void IMSavedValues::setAlcLvl(uint16_t value) {
  alcLvl = value;
}

void IMSavedValues::setSteamTemp(float value) {
  steamTemp = value;
}

void IMSavedValues::setCondTemp(float value) {
  condTemp = value;
}

void IMSavedValues::setPipeTemp(float value) {
  pipeTemp = value;
}

void IMSavedValues::setEnvTemp(float value) {
  envTemp = value;
}

void IMSavedValues::setPressure(float value) {
  pressure = value;
}
