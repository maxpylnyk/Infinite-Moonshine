#include "IMStepMotor.h"

IMStepMotor::IMStepMotor(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) :
  pins({pin1, pin2, pin3, pin4}), seqCounter(0), currentPosition(0), targetPosition(0) {
  for (int i = 0; i < pinsCount; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

bool IMStepMotor::setTargetPosition(uint16_t position) {
  if (position < minPosition || position > maxPosition) {
    return false;
  }
  targetPosition = position;
  return true;
}

bool IMStepMotor::setCurrentPosition(uint16_t position) {
  if (position < minPosition || position > maxPosition) {
    return false;
  }
  currentPosition = position;
  return true;
}

uint16_t IMStepMotor::mlToSteps(uint16_t mlH) {
  return mlH;//tbd
}

uint16_t IMStepMotor::stepsToMl(uint16_t steps) {
  return steps;//tbd
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

uint16_t IMStepMotor::getCurrentPosition() {
  return currentPosition;
}

uint16_t IMStepMotor::getTargetPosition() {
  return targetPosition;
}

bool IMStepMotor::setFlow(uint16_t mlH) {
  Serial.println("setFlow(): flow to set "+String(mlH));
  uint16_t steps = mlToSteps(mlH);
  Serial.println("setFlow(): steps to set "+String(steps));
  setTargetPosition(steps);
}

uint16_t IMStepMotor::getFlow() {
  uint16_t steps = getTargetPosition();
  return stepsToMl(steps);
}

void IMStepMotor::loop() {
  if (onPosition()) {
    return;
  }
  if (micros() - lastStepTime < getPauseUS()) {
    return;
  }
  uint32_t stepsToMove = getTargetPosition() - getCurrentPosition();
  uint32_t position = 0;

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
  //Serial.println("loop(): stepsToMove: "+String(stepsToMove));
  //Serial.println("loop(): seq: "+String(seqCounter));
  //Serial.println("loop(): position: "+String(position));
  setCurrentPosition(position);
  move();
  lastStepTime = micros();

  if (onPosition()) {
    //Serial.println("loop(): sequence completed");
    disableMagnets();
  }
}

void IMStepMotor::move() {
  move(seqCounter);
}

void IMStepMotor::disableMagnets() {
  seqCounter = 0;
  move();
}

void IMStepMotor::move(uint8_t step) {
  switch(step) {
#if defined(INVERT)
    case 4:
      pattern[0] = 1;
      pattern[1] = 1;
      pattern[2] = 0;
      pattern[3] = 0;
      break;
    case 3:
      pattern[0] = 0;
      pattern[1] = 1;
      pattern[2] = 1;
      pattern[3] = 0;
      break;
    case 2:
      pattern[0] = 0;
      pattern[1] = 0;
      pattern[2] = 1;
      pattern[3] = 1;
      break;
    case 1:
      pattern[0] = 1;
      pattern[1] = 0;
      pattern[2] = 0;
      pattern[3] = 1;
      break;
#else
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
#endif
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
