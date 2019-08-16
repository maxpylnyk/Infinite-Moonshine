#ifndef IM_RECT_H
#define IM_RECT_H

#include "utilities/IMPoint.h"

class IMRect {
  private:
    int xLo, yLo, xHi, yHi;
    int xCenter, yCenter;

  public:
    IMRect(int xLo, int yLo, int xHi, int yHi);

    IMPoint getCenter();
    bool hasPoint(IMPoint p);

    int getXLo();
    int getXHi();
    int getYLo();
    int getYHi();
    int getWidth();
    int getHeight();

};

#endif
