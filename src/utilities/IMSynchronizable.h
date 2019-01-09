#ifndef IM_SYNCHRONIZABLE_H
#define IM_SYNCHRONIZABLE_H

#include "stdint.h"

class IMSynchronizable {
  private:
    static const uint16_t roundReserve = 10;
    static const uint16_t floatPrecision = 1000;

    int8_t arraySize;

    int16_t toShort(uint8_t byte1, uint8_t byte2);
    uint16_t toUShort(uint8_t byte1, uint8_t byte2);
    void toArray(uint16_t data, uint8_t bytes[]);

  protected:
    static const int8_t byteSize = 1;
    static const int8_t shortSize = 2;
    static const int8_t floatSize = 4;

    int16_t toShort(uint8_t bytes[]);
    uint32_t toUInt(uint8_t bytes[]);
    float toFloat(uint8_t bytes[]);

    void toArray(int16_t data, uint8_t bytes[]);
    void toArray(uint32_t data, uint8_t bytes[]);
    void toArray(float data, uint8_t bytes[]);

  public:
    IMSynchronizable(int8_t arraySize);

    int8_t getSyncArraySize();
    virtual void getSyncArray(uint8_t bytes[]) = 0;
    virtual void sync(uint8_t bytes[]) = 0;

};

#endif
