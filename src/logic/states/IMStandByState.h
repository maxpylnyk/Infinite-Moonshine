#ifndef IM_STANDBY_STATE_H
#define IM_STANDBY_STATE_H

#include "IMState.h"

class IMStandByState : public IMState {
  public:
    IMStandByState();

    void init();
    void loop();
    IMState * nextState();
    
};

#endif
