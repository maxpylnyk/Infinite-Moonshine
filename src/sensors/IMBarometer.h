#ifndef IM_BAROMETER_H
#define IM_BAROMETER_H

#include "sensors/IMSensor.h"
#include "Wire.h"
#include "SFE_BMP180.h"
#include "utilities/IMDecimal.h"

class IMBarometer : public IMSensor {
  private:
    static const char resolution = 3;
    static const float treshold = 650.0;
    static const float mmHgMultiplier = 0.75;
    static const unsigned int initTime = 0;
    static const unsigned int requestTime = 27;
    static const unsigned int receiveTime = 1;
    float pressure;
    double p, t;
    IMDecimal temp;
    SFE_BMP180 sensor;

    void setPressure(double);

  public:
    IMBarometer();

    bool init();
    void debug();
    void requestData();
    void receiveData();
    float getPressure();

};

#endif
