#ifndef IM_POINT_H
#define IM_POINT_H

class IMPoint {
  public:
    IMPoint();
    IMPoint(int x, int y, int z=0);

    bool operator==(IMPoint);
    bool operator!=(IMPoint);
    bool hasValue();

    int x, y, z;
};

#endif
