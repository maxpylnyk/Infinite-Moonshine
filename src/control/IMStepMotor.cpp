#include "IMStepMotor.h"

IMStepMotor::IMStepMotor(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) :
  IMSynchronizable(syncBytesCount), pins({pin1, pin2, pin3, pin4}), seqCounter(0), currentPosition(0), targetPosition(0) {
  for (int i = 0; i < pinsCount; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

bool IMStepMotor::setTargetPosition(int32_t position) {
  if (position < minPosition || position > maxPosition) {
    return false;
  }
  targetPosition = position;
  return true;
}

bool IMStepMotor::setCurrentPosition(int32_t position) {
  if (position < minPosition || position > maxPosition) {
    return false;
  }
  currentPosition = position;
  return true;
}

int32_t IMStepMotor::mlToSteps(int16_t mlH) {
  return mlH;//tbd
}

int16_t IMStepMotor::stepsToMl(int32_t steps) {
  return (int16_t) steps;//tbd
}

static unsigned long IMStepMotor::getPauseUS() {
  return pauseUS;
}

bool IMStepMotor::increase() {
  int position = getTargetPosition() + adjStep;
  return setTargetPosition(position);
}

bool IMStepMotor::decrease() {
  int position = getTargetPosition() - adjStep;
  return setTargetPosition(position);
}

bool IMStepMotor::zeroPosition() {
  return setTargetPosition(minPosition);
}

bool IMStepMotor::onPosition() {
  return getCurrentPosition() == getTargetPosition();
}

int32_t IMStepMotor::getCurrentPosition() {
  return currentPosition;
}

int32_t IMStepMotor::getTargetPosition() {
  return targetPosition;
}

bool IMStepMotor::setFlow(int16_t mlH) {
  Serial.println("flow to set "+String(mlH));
  int32_t steps = mlToSteps(mlH);
  Serial.println("steps to set "+String(steps));
  setTargetPosition(steps);
}

int16_t IMStepMotor::getFlow() {
  int32_t steps = getTargetPosition();
  return stepsToMl(steps);
}

void IMStepMotor::loop() {
  if (micros() - lastStepTime < getPauseUS()) {
    return;
  }
  int32_t stepsToMove = getTargetPosition() - getCurrentPosition();
  int32_t position = 0;

  if (stepsToMove > 0) {
    seqCounter += 1;

    if (seqCounter > seqSize) {
      seqCounter = 1;
    }
    position = getCurrentPosition() + 1;
  } else if (stepsToMove < 0) {
    seqCounter -= 1;

    if (seqCounter < 1) {
      seqCounter = seqSize;
    }
    position = getCurrentPosition() - 1;
  } else {
    seqCounter = 0;
  }
  move();

  if (position != 0) {
    setCurrentPosition(position);
  }
  if (stepsToMove == 1 || stepsToMove == -1) {
    loop();
  }
  lastStepTime = micros();
}

void IMStepMotor::move() {
  switch(seqCounter) {
    case 1:
      pattern[0] = 1;
      pattern[1] = 1;
      pattern[2] = 0;
      pattern[3] = 0;
      break;
    case 2:
      pattern[0] = 0;
      pattern[1] = 1;
      pattern[2] = 1;
      pattern[3] = 0;
      break;
    case 3:
      pattern[0] = 0;
      pattern[1] = 0;
      pattern[2] = 1;
      pattern[3] = 1;
      break;
    case 4:
      pattern[0] = 1;
      pattern[1] = 0;
      pattern[2] = 0;
      pattern[3] = 1;
      break;
    default:
      pattern[0] = 0;
      pattern[1] = 0;
      pattern[2] = 0;
      pattern[3] = 0;
  }
  for (int i = 0; i < pinsCount; i++) {
    digitalWrite(pins[i], pattern[i]);
  }
}

void IMStepMotor::getSyncArray(uint8_t bytes[]) {
  toArray(getFlow(), *bytes);
}

void IMStepMotor::sync(uint8_t bytes[]) {
  int16_t flow = toShort(*bytes);

  setFlow(flow);
}
