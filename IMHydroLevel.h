#ifndef IM_HYDROLEVEL_H
#define IM_HYDROLEVEL_H

#include "IMSensor.h"

#define OUT_PIN       5
#define LO_PIN        A1
#define HI_PIN        A2
#define OVERFLOW_PIN  A3

class IMHydroLevel : public IMSensor {
  private:
    static const int8_t syncBytesCount = 1;
    static const int treshold = 100;
    static const unsigned int requestTime = 0;
    static const unsigned int receiveTime = 0;
    static const float refResistorLo = 2.7;
    static const float refResistorHi = 2.7;
    static const float refResistorOver = 2.7;

    int dataLo;
    int dataHi;
    int dataOver;
    IMLevel level;

    void setDataLo(int data);
    int getDataLo();
    void setDataHi(int data);
    int getDataHi();
    void setDataOver(int data);
    int getDataOver();
    bool loReached();
    bool hiReached();
    bool overReached();
    void setLevel(IMLevel level);

  public:
    IMHydroLevel();

    bool init();
    void debug();
    void requestData();
    void receiveData();
    uint8_t[] getSyncArray();
    void sync(uint8_t[] array);
    IMLevel getLevel();
    bool isOverflowing();

    enum IMLevel : int8_t {
      LOW = 0,
      MID = 1,
      HIGH = 3,
      OVERFLOW = 7
    };

};

#endif
