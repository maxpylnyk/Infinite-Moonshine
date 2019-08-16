#include "IMRect.h"

IMRect::IMRect(int xLo, int yLo, int xHi, int yHi) 
  : xLo(xLo), yLo(yLo), xHi(xHi), yHi(yHi) {
    xCenter = (xLo + xHi) / 2;
    yCenter = (yLo + yHi) / 2;
}

IMPoint IMRect::getCenter() {
  return IMPoint(xCenter, yCenter);
}

bool IMRect::hasPoint(IMPoint p) {
  return p.x >= xLo && p.x <= xHi && p.y >= yLo && p.y <= yHi;
}

int IMRect::getXLo() {
  return xLo;
}

int IMRect::getXHi() {
  return xHi;
}

int IMRect::getYLo() {
  return yLo;
}

int IMRect::getYHi() {
  return yHi;
}

int IMRect::getWidth() {
  return xHi - xLo;
}

int IMRect::getHeight() {
  return yHi - yLo;
}
