#ifndef IM_SENSOR_H
#define IM_SENSOR_H

#include "stdint.h"
#include "Arduino.h"
#include "utilities/IMCommons.h"
#include "utilities/IMTimer.h"

class IMSensor {
  private:
    bool measuring;
    bool measured;
    unsigned long lastRequestTime;
    unsigned long lastMeasureTime;
    unsigned long timeout;
    uint32_t initTime;
    uint32_t requestTime;
    uint32_t receiveTime;

  protected:
    IMTimer stopwatch;

    void setMeasuring(bool);
    void setMeasured(bool);

  public:
    IMSensor(uint32_t initTime, uint32_t requestTime, 
      uint32_t receiveTime, unsigned long timeout);
    
    virtual bool init() = 0;
    virtual void debug();
    bool isMeasuring();
    bool dataReady();
    uint32_t getInitTime();
    uint32_t getRequestTime();
    uint32_t getReceiveTime();
    unsigned long getMeasuringTime();
    virtual void requestData();
    virtual void receiveData();
    bool collectReadings();
    void prepareToCollect();

};

#endif
