#ifndef IM_SWITCH_H
#define IM_SWITCH_H

#include "control/IMStepMotor.h"

class IMSwitch {
  private:
    static const int16_t HEAD_POS = 0;
    static const int16_t BODY_POS = 1000;
    
    IMStepMotor * swMtr;

  public:
    IMSwitch() {};

    void setMotor(IMStepMotor * mtr) {
      swMtr = mtr;
    }

    uint8_t getSwitchPos() {
      if (swMtr->getCurrentPosition()) {
        return 1;
      }
      return 0;
    }

    void setSwitchPos(uint8_t value) {
      if (value) {
        swMtr->setTargetPosition(BODY_POS);
      } else {
        swMtr->setTargetPosition(HEAD_POS);
      }
    }

};

#endif
