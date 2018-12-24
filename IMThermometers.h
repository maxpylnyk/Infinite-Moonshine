#ifndef IM_THERMOMETERS_H
#define IM_THERMOMETERS_H

#include "IMSensor.h"
#include "IMThermometer.h"
#include "OneWire.h"
#include "DallasTemperature.h"

#define THERMOMETERS_PIN  2

class IMThermometers : public IMSensor {
  private:
    static const float t1Adj = 1.25;
    static const float t2Adj = 0.875;
    static const float t3Adj = 1.125;
    static const float t4Adj = 1.313;
    static const uint8_t[] t1Address = {0x28, 0xFF, 0x44, 0x18, 0x03, 0x17, 0x04, 0x9D};
    static const uint8_t[] t2Address = {0x28, 0xFF, 0xAA, 0xD7, 0x02, 0x17, 0x04, 0xED};
    static const uint8_t[] t3Address = {0x28, 0xFF, 0x25, 0x1A, 0x03, 0x17, 0x04, 0x46};
    static const uint8_t[] t4Address = {0x28, 0xFF, 0x8D, 0x89, 0x02, 0x17, 0x05, 0xD7};
    static const uint8_t thermometersCount = 3;
    static const uint8_t resolution = 12;
    static const int8_t syncBytesCount = floatSize * thermometersCount;
    static const unsigned int requestTime = 3;
    static const unsigned int receiveTime = 50 + 50 * thermometersCount;

    OneWire wire(THERMOMETERS_PIN);
    DallasTemperature tempSensors(&wire);
    IMThermometer steamTherm;
    IMThermometer condTherm;
    IMThermometer pipeTherm;

    bool initThermometer(IMThermometer& t, DeviceAddress address, float adjustment);

  public:
    IMThermometers();

    bool init();
    void debug();
    void requestData();
    void receiveData();
    uint8_t[] getSyncArray();
    void sync(uint8_t[] array);
    float getSteamTemp();
    float getCondTemp();
    float getPipeTemp();

};

#endif
