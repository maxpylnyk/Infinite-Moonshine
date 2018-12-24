#include "IMPoint.h"

IMPoint::IMPoint() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

IMPoint::IMPoint(int16_t x, int16_t y, int16_t z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

bool IMPoint::operator==(IMPoint other) {
  return this->x == other.x && this->y == other.y && this->z == other.z;
}

bool IMPoint::operator!=(IMPoint other) {
  return this->x != other.x || this->y != other.y || this->z != other.z;
}

bool IMPoint::hasValue() {
  return this->x != 0 || this->y != 0 || this->z != 0;
}