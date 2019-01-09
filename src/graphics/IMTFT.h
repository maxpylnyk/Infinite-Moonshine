#ifndef IM_TFT_H
#define IM_TFT_H

#include "stdint.h"
#include "graphics/IMRect.h"
#include "Arduino.h"
#include "UTFTGLUE.h"

class IMTFT {
  private:
    const uint8_t RS = A2;
    const uint8_t WR = A1;
    const uint8_t CS = A3;
    const uint8_t RST = A4;
    const uint8_t RD = A0;
    const byte ID = 0x9325;

    UTFTGLUE tft = UTFTGLUE(ID, RS, WR, CS, RST, RD);

  public:
    IMTFT();

    bool init();
    void setColor(uint32_t color);
    void setColor(uint16_t color);
    void paintBackground();
    void drawLine(int x1, int y1, int x2, int y2);
    void drawCircle(int x0, int y0, int r);
    void fillRect(IMRect r);
    void fillRect(int x1, int y1, int x2, int y2);
    void fillCircle(int x0, int y0, int r);
    void print(String text, int x, int y);

};

#endif
