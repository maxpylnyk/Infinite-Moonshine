#ifndef IM_HYDROLEVEL_H
#define IM_HYDROLEVEL_H

#include "sensors/IMSensor.h"

#define OUT_PIN       5
#define LO_PIN        A1
#define HI_PIN        A2
#define OVR_PIN       A3

typedef enum {
  LO      = 0x00,
  OK      = 0x01,
  HI      = 0x03,
  OVR     = 0x07
} IMLevel;

class IMHydroLevel : public IMSensor {
  private:
    static const int8_t syncBytesCount = 1;
    static const int treshold = 100;
    static const unsigned int initTime = 0;
    static const unsigned int requestTime = 0;
    static const unsigned int receiveTime = 0;
    static const float refResistorLo = 2.7;
    static const float refResistorHi = 2.7;
    static const float refResistorOver = 2.7;

    int dataLo;
    int dataHi;
    int dataOver;
    IMLevel level;

    void setDataLo(int);
    int getDataLo();
    void setDataHi(int);
    int getDataHi();
    void setDataOver(int);
    int getDataOver();
    bool loReached();
    bool hiReached();
    bool overReached();
    void setLevel(IMLevel);

  public:
    IMHydroLevel();

    bool init();
    void debug();
    void requestData();
    void receiveData();
    void getSyncArray(uint8_t bytes[]);
    void sync(uint8_t bytes[]);
    IMLevel getLevel();
    bool isOverflowing();   

};

#endif
