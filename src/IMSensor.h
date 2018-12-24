#ifndef IM_SENSOR_H
#define IM_SENSOR_H

#include "IMSynchronizable.h"
#include "Arduino.h"

class IMSensor : public IMSynchronizable {
  private:
    bool measuring;
    uint32_t initTime;
    uint32_t requestTime;
    uint32_t receiveTime;

  protected:
    void setMeasuring(bool value);

  public:
    IMSensor(int8_t arraySize, uint32_t initTime, uint32_t requestTime, uint32_t receiveTime);
    virtual ~IMSensor() = 0;
    
    virtual bool init() = 0;
    virtual void debug() = 0;
    bool isMeasuring();
    uint32_t getInitTime();
    uint32_t getRequestTime();
    uint32_t getReceiveTime();
    unsigned long getMeasuringTime();
    virtual void requestData() = 0;
    virtual void receiveData() = 0;

};

#endif
