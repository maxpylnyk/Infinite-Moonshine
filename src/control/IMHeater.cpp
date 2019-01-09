#include "IMHeater.h"

IMHeater::IMHeater(uint8_t powerHead, uint8_t powerBody, uint8_t adjStep) :
 IMSynchronizable(syncBytesCount), powerHead(powerHead), powerBody(powerBody), adjStep(adjStep) {
  pinMode(SSR_PIN, OUTPUT);
  off();
}

bool IMHeater::setAdjStep(uint8_t value) {
  if (value >= minAdjStep && value <= maxAdjStep) {
    adjStep = value;
    return true;
  }
  return false;
}

void IMHeater::setPower(uint8_t value) {
  analogWrite(SSR_PIN, power);
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

void IMHeater::minBoilingValue() {
  setPower(powerMin);
  prevCall = FIXED;
  coarseCounter = 0;
  fineCounter = 0;
}

void IMHeater::headValue() {
  setPower(powerHead);
  prevCall = FIXED;
  coarseCounter = 0;
  fineCounter = 0;
}

void IMHeater::bodyValue() {
  setPower(powerBody);
  prevCall = FIXED;
  coarseCounter = 0;
  fineCounter = 0;
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

void IMHeater::getSyncArray(uint8_t bytes[]) {
  toArray(getPower(), *bytes);
  toArray(getAdjStep(), *(bytes+byteSize));
}

void IMHeater::sync(uint8_t bytes[]) {
  uint8_t temp = bytes[0];

  setPower(temp);

  temp = bytes[1];
  setAdjStep(temp);
}
