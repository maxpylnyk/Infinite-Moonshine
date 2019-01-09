#include "IMState.h"

IMState::IMState(uint8_t stateIndex) : state(stateIndex) {
  setPercents(0);
}

uint8_t IMState::getStateIndex() {
  return state;
}

bool IMState::isEnabled() {
  return enabled;
}

int8_t IMState::getPercents() {
  return percents;
}

void IMState::setPercents(int8_t pct) {
  if (pct >=0 && pct <= 100) {
    percents = pct;
  }
}

void IMState::setEnabled(bool value) {
  enabled = value;
}
