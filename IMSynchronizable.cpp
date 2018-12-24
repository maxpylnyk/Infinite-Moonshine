#include "IMSynchronizable.h"

IMSynchronizable::IMSynchronizable(int8_t arraySize) : arraySize(arraySize) {}

int16_t IMSynchronizable::toShort(uint8_t byte1, uint8_t byte2) {
  int16_t data = 0;

  data |= byte1;
  data <<= 8;
  data |= byte2;

  return data;
}

uint16_t IMSynchronizable::toUShort(uint8_t byte1, uint8_t byte2) {
  uint16_t data = 0;

  data |= byte1;
  data <<= 8;
  data |= byte2;

  return data;
}

int16_t IMSynchronizable::toShort(uint8_t bytes[]) {
  return toShort(bytes[0], bytes[1]);
}

uint32_t IMSynchronizable::toUInt(uint8_t bytes[]) {
  int shifts = 3;
  uint32_t data = 0;

  for (int i = 0; i < shifts; i++) {
    data |= bytes[i];
    data <<= 8;
  }
  data |= bytes[shifts];
  return data;
}

float IMSynchronizable::toFloat(uint8_t bytes[]) {
  int16_t whole = 0;
  uint16_t fract = 0;
  uint32_t divisor = 1;
  float data = 0;

  whole = toShort(bytes);
  fract = toUShort(bytes[2], bytes[3]);

  while (fract / divisor > 0) {
    divisor *= 10;
  }
  data = (1.0 * fract) / (1.0 * divisor);

  if (whole < 0) {
    data *= -1;
  }
  data += whole;

  return data;
}

void IMSynchronizable::toArray(uint16_t data, uint8_t bytes[]) {
  bytes[0] = data >> 8;
  bytes[1] = data & 0x00FF;
}

void IMSynchronizable::toArray(int16_t data, uint8_t bytes[]) {
  bytes[0] = data >> 8;
  bytes[1] = data & 0x00FF;
}

void IMSynchronizable::toArray(uint32_t data, uint8_t bytes[]) {
  bytes[0] = data >> 24;
  bytes[1] = (data >> 16) & 0x00FF;
  bytes[2] = (data >> 8) & 0x0000FF;
  bytes[3] = data & 0x000000FF;
}

void IMSynchronizable::toArray(float data, uint8_t bytes[]) {
  int16_t whole;
  uint16_t fract;
  uint8_t buffer[shortSize];
  float temp;

  whole = data;
  toArray(whole, buffer);
  bytes[0] = buffer[0];
  bytes[1] = buffer[1];

  temp = (data - whole);

  if (whole < 0) {
    temp *= -1;
  }
  temp *= floatPrecision * roundReserve;
  fract = temp;

  if (fract % roundReserve >= 5) {
    fract += roundReserve;
  }
  fract /= roundReserve;
  toArray(fract, buffer);
  bytes[2] = buffer[0];
  bytes[3] = buffer[1];
}

int8_t IMSynchronizable::getSyncArraySize() {
  return arraySize;
}
