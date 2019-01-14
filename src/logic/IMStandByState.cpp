#include "IMStandByState.h"

IMStandByState::IMStandByState() : IMState(STAND_BY_STATE) {}

void IMStandByState::init() {

}

void IMStandByState::loop() {

}

IMState * IMStandByState::nextState() {
  return 0;//&IMHeatState();
}