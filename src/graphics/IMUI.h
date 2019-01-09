#ifndef IM_UI_H
#define IM_UI_H

#include "graphics/IMTFT.h"
#include "graphics/IMTouchScreen.h"
#include "graphics/IMPane.h"

class IMPane;

class IMUI {
  private:
    IMTFT tft;
    IMTouchScreen ts;
    IMPane * currentPane;

  public:
    static const uint16_t MAIN_COLOR =         0x97fc;//0x94ffe6;
    static const uint16_t MAIN_COLOR_FLAT =    0x3b4c;//0x3e6b62;
    static const uint16_t HEAT_COLOR =         0xffa0;//0xfff700;
    static const uint16_t STAB_COLOR =         0xfba0;//0xff7700;
    static const uint16_t HEAD_COLOR =         0xf800;//0xff0000;
    static const uint16_t AROMA_COLOR =        0xf81f;//0xff00ff;
    static const uint16_t BODY_COLOR =         0xffff;//0xffffff;
    static const uint16_t TAIL_COLOR =         0x045f;//0x0088ff;
    static const uint16_t BACKGROUND_COLOR =   0x0000;//0x000000;

    static const uint16_t HEIGHT = 240;
    static const uint16_t WIDTH  = 320;

    static const int8_t LINE_WIDTH = 2;
    static const int8_t LINE_RADIUS = LINE_WIDTH / 2;

    static const uint16_t INFINITY_WIDTH  = 276;
    static const uint16_t BUTTONS_WIDTH   = 71;
    static const uint16_t BAR_HEIGHT      = 71;

    IMUI();

    bool init();
    void handleTouch();
    IMTFT * getTFT();

};

#endif
