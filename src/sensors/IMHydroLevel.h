#ifndef IM_HYDROLEVEL_H
#define IM_HYDROLEVEL_H

#include "sensors/IMSensor.h"

typedef enum IMLevel : uint8_t {
  LO      = 0x0,
  OK      = 0x1,
  HI      = 0x3,
  OVR     = 0x7
};

class IMHydroLevel : public IMSensor {
  private:
    static const int treshold = 400;
    static const unsigned int initTime = 0;
    static const unsigned int requestTime = 0;
    static const unsigned int receiveTime = 0;
    static const float refResistorLo = 2.7;
    static const float refResistorHi = 3.3;
    static const float refResistorOver = 4.7;

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
    IMLevel getLevel();
    bool isOverflowing();   

};

#endif
