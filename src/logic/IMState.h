#ifndef IM_STATE_H
#define IM_STATE_H

#include "stdint.h"

typedef enum StateIndex : uint8_t {
  STAND_BY_STATE = 0,
  HEAT_STATE,
  STAB_STATE,
  HEAD_STATE,
  PRE_BODY_STATE,
  BODY_STATE,
  PRE_TAIL_STATE,
  FINISH_STATE,
  CANCEL_STATE,
  ERROR_STATE
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
