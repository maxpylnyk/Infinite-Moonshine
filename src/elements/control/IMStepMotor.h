#ifndef IM_STEP_MOTOR_H
#define IM_STEP_MOTOR_H

#include "stdint.h"
#include "Arduino.h"

#define INVERT  1

class IMStepMotor {
  private:
    static const int8_t seqSize = 4;
    static const uint8_t pinsCount = 4;
    static const uint8_t roundsPerMinute = 12;
    static const uint16_t stepsPerRound = 2048;
    static const int16_t minPosition = 0;
    static const int16_t maxPosition = INT16_MAX;
    static const unsigned long minuteUS = 60000000;
    static const unsigned long pauseUS = -1.6 * roundsPerMinute + minuteUS / ((unsigned long) stepsPerRound * roundsPerMinute);
    int8_t seqCounter;
    uint8_t pins[pinsCount];
    uint8_t pattern[pinsCount];
    int16_t currentPosition;
    int16_t targetPosition;
    unsigned long lastStepTime;

    void move();
    void move(int8_t);
    void disableMagnets();

  public:
    IMStepMotor(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);

    unsigned long getPauseUS();
    bool onPosition();
    bool zeroPosition();
    bool setCurrentPosition(int16_t);
    bool setTargetPosition(int16_t);
    int16_t getCurrentPosition();
    int16_t getTargetPosition();
    bool loop();
    bool isMoving();

};

#endif
