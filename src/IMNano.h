#ifndef IM_NANO_H
#define IM_NANO_H

#include "InfiniteMoonshine.h"

class IMNano : public InfiniteMoonshine { //manual pause only
  private:
    bool resumePrevSession = false;

    void sendData();
    void receiveData();

  public:
    IMNano();

    bool init();
    void loop();
    void debug();
    void receiveCallsign();
    
};

#endif
