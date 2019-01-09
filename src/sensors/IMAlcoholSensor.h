#ifndef IM_ALCOHOL_SENSOR_H
#define IM_ALCOHOL_SENSOR_H

#include "sensors/IMSensor.h"

#define HEAT_PIN  4
#define DATA_PIN  A0

class IMAlcoholSensor : public IMSensor {
  private:
    static const int8_t syncBytesCount = shortSize;
    static const uint16_t treshold = 240;
    static const uint32_t initTime = 0;
    static const uint32_t requestTime = 60 * 1000; //needs optimization
    static const uint32_t receiveTime = 5;

    int16_t value;

    void setValue(int16_t data);

  public:
    IMAlcoholSensor();

    bool init();
    void debug();
    bool ethanolDetected();
    int16_t getValue();
    void getSyncArray(uint8_t bytes[]);
    void sync(uint8_t bytes[]);
    void requestData();
    void receiveData();

};

#endif
