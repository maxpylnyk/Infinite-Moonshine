#ifndef IM_TOUCH_SCREEN_H
#define IM_TOUCH_SCREEN_H

#define NUMSAMPLES 3

#include "utilities/IMPoint.h"
#include "graphics/IMTFT.h"
#include "Arduino.h"

class IMTouchScreen {
  private:
    static const uint8_t YP = A1;
    static const uint8_t XM = A2;
    static const uint8_t YM = 7;
    static const uint8_t XP = 6;
    static const uint16_t RX = 300;

    static const uint16_t TS_LEFT = 184;
    static const uint16_t TS_RT  = 932;
    static const uint16_t TS_TOP = 939;
    static const uint16_t TS_BOT = 203;

    static const int16_t LO_TRESHOLD = 200;
    static const int16_t HI_TRESHOLD = 1000;

    IMPoint getPoint();

  public:
    IMTouchScreen();

    bool init();
    IMPoint getTouchPosition();

};

#endif
