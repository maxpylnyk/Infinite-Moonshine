#include "IMTFT.h"
#include "graphics/IMUI.h"

IMTFT::IMTFT() {}

bool IMTFT::init() {
  tft.InitLCD();
  tft.setFont(NULL);
  tft.setTextSize(2);
  return true;
}

void IMTFT::setColor(uint32_t color) {
  byte r, g, b;

  r = (color & 0xFF0000) >> 16;
  g = (color & 0xFF00) >> 8;
  b = color & 0xFF;

  //Serial.println(String(tft.setrgb(r,g,b), HEX));

  tft.setColor(r, g, b);
}

void IMTFT::setColor(uint16_t color) {
  tft.setColor(color);
}

void IMTFT::paintBackground() {
  tft.fillScreen(IMUI::BACKGROUND_COLOR);
}

void IMTFT::drawLine(int x1, int y1, int x2, int y2) {
  tft.drawLine(x1, IMUI::HEIGHT - y1, x2, IMUI::HEIGHT - y2);
}

void IMTFT::drawCircle(int x0, int y0, int r) {
  tft.drawCircle(x0, IMUI::HEIGHT - y0, r);
}

void IMTFT::fillRect(IMRect r) {
  fillRect(r.getXLo(), r.getYLo(), r.getXHi(), r.getYHi());
}

void IMTFT::fillRect(int x1, int y1, int x2, int y2) {
  tft.fillRect(x1, IMUI::HEIGHT - y1, x2, IMUI::HEIGHT - y2);
}

void IMTFT::fillCircle(int x0, int y0, int r) {
  tft.fillCircle(x0, IMUI::HEIGHT - y0, r);
}

void IMTFT::print(String text, int x, int y) {
  tft.print(text, x, IMUI::HEIGHT - y);
}
