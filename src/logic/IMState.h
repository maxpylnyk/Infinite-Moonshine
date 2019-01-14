#ifndef IM_STATE_H
#define IM_STATE_H

#include "stdint.h"

typedef enum StateIndex : uint8_t {
  STAND_BY_STATE = 0x00,
  HEAT_STATE     = 0x10,
  STAB_STATE     = 0x20,
  HEAD_STATE     = 0x30,
  PRE_BODY_STATE = 0x40,
  BODY_STATE     = 0x50,
  PRE_TAIL_STATE = 0x60,
  FINISH_STATE   = 0x70,
  CANCEL_STATE   = 0x80,
  MANUAL_MODE    = 0xA0,
  ERROR_STATE    = 0xF0
};

class IMState {
	private:
    bool enabled;
    int8_t state;
    int8_t percents;

  protected:
    void setEnabled(bool);
    void setPercents(int8_t);

  public:
    IMState(uint8_t stateIndex);

    uint8_t getStateIndex();
    bool isEnabled();
    int8_t getPercents();

    virtual void init() = 0;
    virtual void loop();
    virtual IMState * nextState();

};

#endif
