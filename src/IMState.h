#ifndef IM_STATE_H
#define IM_STATE_H

#include "stdint.h"

class IMState {
	private:
    bool enabled;
    int8_t state;

  public:
    IMState(uint8_t stateIndex);
    virtual ~IMState() = 0;

    virtual IMState nextState() = 0;
    uint8_t getStateIndex();
    bool isEnabled();
    

    enum StateIndex : uint8_t {
      STAND_BY_STATE = 0x00,
      INIT_STATE     = 0x10,
      STAB_STATE     = 0x20,
      HEAD_STATE     = 0x30,
      PRE_BODY_STATE = 0x40,
      BODY_STATE     = 0x50,
      PRE_TAIL_STATE = 0x60,
      FINISH_STATE   = 0x70,
      CANCEL_STATE   = 0x80,
      ERROR_STATE    = 0xF0
    };

};

#endif
