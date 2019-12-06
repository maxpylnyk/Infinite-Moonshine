#ifndef IM_STEP_MOTOR_H
#define IM_STEP_MOTOR_H

#include "stdint.h"
#include "Arduino.h"

#define INVERT  1

class IMStepMotor {
  private:
    static const uint8_t pinsCount = 4;
    static const uint8_t adjStep = 1;
    static const uint8_t seqSize = 4;
    static const uint8_t roundsPerMinute = 12;
    static const uint16_t stepsPerRound = 2048;
    static const uint16_t minPosition = 0;
    static const uint16_t maxPosition = UINT16_MAX;
    static const unsigned long minuteUS = 60000000;
    static const unsigned long pauseUS = -1.6 * roundsPerMinute + minuteUS / ((unsigned long) stepsPerRound * roundsPerMinute);
    uint8_t seqCounter;
    uint8_t pins[pinsCount];
    uint8_t pattern[pinsCount];
    uint16_t currentPosition;
    uint16_t targetPosition;
    unsigned long lastStepTime;

    uint16_t mlToSteps(uint16_t);
    uint16_t stepsToMl(uint16_t);
    void move();
    void move(uint8_t);
    void disableMagnets();

  public:
    IMStepMotor(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);

    unsigned long getPauseUS();
    bool increase();
    bool decrease();
    bool onPosition();
    bool zeroPosition();
    bool setCurrentPosition(uint16_t);
    bool setTargetPosition(uint16_t);
    uint16_t getCurrentPosition();
    uint16_t getTargetPosition();
    bool setFlow(uint16_t);
    uint16_t getFlow();
    void loop();

};

#endif
