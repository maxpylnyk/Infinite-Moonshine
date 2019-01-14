#include "InfiniteMoonshine.h"

InfiniteMoonshine::InfiniteMoonshine() {}

StateIndex InfiniteMoonshine::getIndex(uint8_t callsign) {
  switch(callsign & logicMask) {
    case StateIndex::STAND_BY_STATE:
      Serial.println("STAND_BY_STATE");
      return StateIndex::STAND_BY_STATE;
    case StateIndex::HEAT_STATE:
      Serial.println("HEAT_STATE");
      return StateIndex::HEAT_STATE;
    case StateIndex::STAB_STATE:
      Serial.println("STAB_STATE");
      return StateIndex::STAB_STATE;
    case StateIndex::HEAD_STATE:
      Serial.println("HEAD_STATE");
      return StateIndex::HEAD_STATE;
    case StateIndex::PRE_BODY_STATE:
      Serial.println("PRE_BODY_STATE");
      return StateIndex::PRE_BODY_STATE;
    case StateIndex::BODY_STATE:
      Serial.println("BODY_STATE");
      return StateIndex::BODY_STATE;
    case StateIndex::PRE_TAIL_STATE:
      Serial.println("PRE_TAIL_STATE");
      return StateIndex::PRE_TAIL_STATE;
    case StateIndex::FINISH_STATE:
      Serial.println("FINISH_STATE");
      return StateIndex::FINISH_STATE;
    case StateIndex::CANCEL_STATE:
      Serial.println("CANCEL_STATE");
      return StateIndex::CANCEL_STATE;
    case StateIndex::MANUAL_MODE:
      Serial.println("MANUAL_MODE");
      return StateIndex::MANUAL_MODE;
    case StateIndex::ERROR_STATE:
      Serial.println("ERROR_STATE");
      return StateIndex::ERROR_STATE;
    default:
      Serial.println("UNDEFINED STATE");
      return 0xFF;
  }
}

void InfiniteMoonshine::clearArray() {
  for (int i = 0; i < dataArraySize; i++) {
    data[i] = 0;
  }
  dataIndex = 0;
}
