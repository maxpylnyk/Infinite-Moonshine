#ifndef IM_TFT_H
#define IM_TFT_H

#include "stdint.h"
#include "graphics/IMRect.h"
#include "utilities/IMCommons.h"
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
    Language locale;
    UTFTGLUE tft = UTFTGLUE(ID, RS, WR, CS, RST, RD);

    uint8_t fontSize;
    uint16_t color;

    uint8_t getFontSize();
    uint16_t getColor();

  public:
    IMTFT(Language locale);

    bool init();
    void setColor(uint32_t color);
    void setColor(uint16_t color);
    void setFontSize(int size);
    void paintBackground(uint16_t color);
    void paintBackground();
    void drawLine(int x1, int y1, int x2, int y2);
    void drawCircle(int x0, int y0, int r);
    void fillRect(IMRect r);
    void fillRect(int x1, int y1, int x2, int y2);
    void fillCircle(int x0, int y0, int r);
    void print(String text, int size, uint16_t color, int x, int y);
    void print(String text, int size, uint16_t color, IMRect r);
    void print(String text, IMRect r);
    void printNum(String num, IMRect r);
    int getWidth();
    int getHeight();

};

#endif
