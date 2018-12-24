#ifndef IM_POINT_H
#define IM_POINT_H
#include <stdint.h>

class IMPoint {
  public:
    IMPoint();
    IMPoint(int16_t x, int16_t y, int16_t z);

    bool operator==(IMPoint);
    bool operator!=(IMPoint);
    bool hasValue();

    int16_t x, y, z;
};

#endif
