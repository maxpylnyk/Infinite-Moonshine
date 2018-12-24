#ifndef IM_SENSORS_H
#define IM_SENSORS_H

#include "IMSensor.h"

class IMSensors {
  private:

  public:
    IMSensors();

    bool init();
    void debug();
    unsigned long requestData();
    unsigned long receiveData();

};

#endif
