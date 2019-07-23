#ifndef IM_EXTRACT_NODE_H
#define IM_EXTRACT_NODE_H

#include "control/IMStepMotor.h"

class IMExtractNode {
  private:
    uint8_t refluxRatio;
    IMStepMotor outMtr;
    IMStepMotor retMtr;

  public:
    IMExtractNode();


};

#endif
