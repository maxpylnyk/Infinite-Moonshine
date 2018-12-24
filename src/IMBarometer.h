#ifndef IM_BAROMETER_H
#define IM_BAROMETER_H

#include "IMSensor.h"
#include "Wire.h"
#include "SFE_BMP180.h"

#define POWER_PIN 3v3
#define GND_PIN   GND
#define SDA_PIN   20
#define SCL_PIN   21

class IMBarometer : public IMSensor {
  private:
    static const int8_t syncBytesCount = floatSize + floatSize;
    static const char resolution = 1;
    static const float treshold = 650.0;
    static const float mmHgMultiplier = 0.75;
    static const unsigned int requestTime = 14;
    static const unsigned int receiveTime = 1;
    double pressure;
    double envTemp;
    SFE_BMP180 presSensor;

    void setPres(float value);
    void setEnvTemp(float value);

  public:
    IMBarometer();

    bool init();
    void debug();
    void requestData();
    void receiveData();
    uint8_t[] getSyncArray();
    void sync(uint8_t[] array);
    float getPres();
    float getEnvTemp();
    float getTableTemp();

};

#endif
