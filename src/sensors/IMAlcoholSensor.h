#ifndef IM_ALCOHOL_SENSOR_H
#define IM_ALCOHOL_SENSOR_H

#include "sensors/IMSensor.h"

class IMAlcoholSensor : public IMSensor {
  private:
    static const uint16_t treshold = 320;
    static const uint32_t requestTime = 60 * 1000;
    static const uint32_t receiveTime = 5;
    static const uint32_t initTime = requestTime + receiveTime;

    int16_t initLevel = 300;
    int16_t level = 326;

    void setLevel(int16_t);

  public:
    IMAlcoholSensor();

    bool init();
    void debug();
    bool ethanolDetected();
    int16_t getLevel();
    void requestData();
    void receiveData();

};

#endif
