#ifndef IM_STEP_MOTOR_H
#define IM_STEP_MOTOR_H

#include "stdint.h"
#include "Arduino.h"
#include "utilities/IMSynchronizable.h"

class IMStepMotor : public IMSynchronizable {
  private:
    static const int8_t syncBytesCount = shortSize;
    static const uint8_t pinsCount = 4;
    static const uint8_t adjStep = 1;
    static const uint8_t seqSize = 4;
    static const uint8_t roundsPerMinute = 9;
    static const int16_t stepsPerRound = 2048;
    static const int32_t minPosition = 0;
    static const int32_t maxPosition = 2147483647;
    static const unsigned long minuteUS = 60000000;
    static const unsigned long pauseUS = -1.6 * roundsPerMinute + minuteUS / ((unsigned long) stepsPerRound * roundsPerMinute);
    uint8_t seqCounter;
    uint8_t pins[pinsCount];
    uint8_t pattern[pinsCount];
    int32_t currentPosition;
    int32_t targetPosition;
    unsigned long lastStepTime;

    bool setTargetPosition(int32_t position);
    bool setCurrentPosition(int32_t position);
    int32_t mlToSteps(int16_t mlH);
    int16_t stepsToMl(int32_t steps);
    void move();

  public:
    IMStepMotor(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);

    static unsigned long getPauseUS();
    bool increase();
    bool decrease();
    bool onPosition();
    bool zeroPosition();
    int32_t getCurrentPosition();
    int32_t getTargetPosition();
    bool setFlow(int16_t mlH);
    int16_t getFlow();
    void loop();

    void getSyncArray(uint8_t bytes[]);
    void sync(uint8_t bytes[]);

};

#endif
