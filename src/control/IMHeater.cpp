#include "IMHeater.h"

IMHeater::IMHeater() {
  pinMode(PinMap::SSR, OUTPUT);
  setAdjStep(16);
  off();
}

bool IMHeater::setAdjStep(uint8_t value) {
  if (DEBUG_MODE || MANUAL_MODE) {
    adjStep = value;
    return true;
  }
  if (value >= minAdjStep && value <= maxAdjStep) {
    adjStep = value;
    return true;
  }
  return false;
}

void IMHeater::setPower(uint8_t value) {
  analogWrite(PinMap::SSR, power);
  power = value;
}

bool IMHeater::tuneAdjStep() {
  bool result = true;
  uint8_t coef;

  if (coarseCounter >= maxCount) {
    coef = getAdjStep() * adjCoef;
    result = setAdjStep(coef);
    coarseCounter = 0;
  }
  if (fineCounter >= maxCount) {
    coef = getAdjStep() / adjCoef;
    result = setAdjStep(coef);
    fineCounter = 0;
  }
  return result;
}

bool IMHeater::decreaseHeat() {
  if (prevCall == DECREASE) {
    coarseCounter += 1;
  } else if (prevCall == INCREASE) {
    fineCounter += 1;
  }
  prevCall = DECREASE;

  if (tuneAdjStep()) {
    int16_t temp = getPower() - getAdjStep();

    if (temp >= 0) {
      setPower(temp);
      return true;
    }
  }
  return false;
}

bool IMHeater::increaseHeat() {
  bool result;
  int16_t temp;

  if (prevCall == INCREASE) {
    coarseCounter += 1;
  } else if (prevCall == DECREASE) {
    fineCounter += 1;
  }
  prevCall = INCREASE;

  if (tuneAdjStep()) {
    int16_t temp = getPower() + getAdjStep();

    if (temp <= powerMax) {
      setPower(temp);
      return true;
    }
  }
  return false;
}

void IMHeater::off() {
  setPower(powerOff);
  prevCall = FIXED;
  coarseCounter = 0;
  fineCounter = 0;
}

void IMHeater::setInitPower(uint8_t pwr) {
  setPower(pwr);
  prevCall = FIXED;
  coarseCounter = 0;
  fineCounter = 0;
}

void IMHeater::setInitAdj(uint8_t adj) {
  setAdjStep(adj);
}

void IMHeater::maxValue() {
  setPower(powerMax);
  prevCall = FIXED;
  coarseCounter = 0;
  fineCounter = 0;
}

uint8_t IMHeater::getPower() {
  return power;
}

uint8_t IMHeater::getAdjStep() {
  return adjStep;
}
