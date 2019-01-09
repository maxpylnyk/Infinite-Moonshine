#include "IMStepMotor.h"

uint8_t motorPin1 = 22;
uint8_t motorPin2 = 23;
uint8_t motorPin3 = 24;
uint8_t motorPin4 = 25;

unsigned long pauseUS;
unsigned long timer;

IMStepMotor mtr(motorPin1, motorPin2, motorPin3, motorPin4);

void setup() {
  int32_t stepsPerRound = 4096;
  int32_t rounds = 10;
  int32_t targetPosition = rounds * stepsPerRound;
  Serial.begin(9600);
  pauseUS = mtr.getPauseUS();
  Serial.println("rounds "+String(rounds)+" steps "+String(stepsPerRound));
  Serial.println("pause "+String(pauseUS)+" us");
  Serial.println("setting motor to "+String(targetPosition)+" : "+String(mtr.setFlow(targetPosition)));
  Serial.println("target position "+String(mtr.getTargetPosition())+" steps");
  timer = micros();
}

void loop(){
  mtr.loop();
  //delayMicroseconds(pauseUS-100);

  //pause * steps * rpm = 1 min
  
  if (mtr.onPosition()) {
    double seconds = (micros() - timer) / 1000000.0;
    double rpm = 60 / seconds;

    //mtr.loop();
    Serial.println("one round in "+String(micros() - timer)+" us");
    Serial.println("one round in "+String(seconds)+" s");
    Serial.println("rotation speed "+String(rpm)+" rpm");
    //timer = micros();
    mtr.zeroPosition();
    delay(10*1000);
  }
  
}
