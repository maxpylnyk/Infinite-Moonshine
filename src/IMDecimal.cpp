#include "IMDecimal.h"

IMDecimal::IMDecimal(float value) {
	parse(value);
}

IMDecimal::IMDecimal() : whole(0), fract(0) {}

bool IMDecimal::operator==(const IMDecimal& other) const {
  return whole == other.whole && fract == other.fract;
}

bool IMDecimal::operator!=(const IMDecimal& other) const {
  return !operator==(other);
}

bool IMDecimal::operator>(const IMDecimal& other) const {
  if (whole == other.whole) {
    return fract > other.fract;
  }
  return whole > other.whole;
}
bool IMDecimal::operator<(const IMDecimal& other) const {
  if (whole == other.whole) {
    return fract < other.fract;
  }
  return whole < other.whole;
}

bool IMDecimal::operator>=(const IMDecimal& other) const {
  return !operator<(other);
}

bool IMDecimal::operator<=(const IMDecimal& other) const {
  return !operator>(other);
}

void IMDecimal::parse(float value) {
  int rest;
  int divisor = precision * roundReserve;
  long temp = value * divisor;

  whole = temp / divisor;
  fract = temp % divisor;
  rest = fract % roundReserve;
  fract /= roundReserve;

  if (rest >= 5) {
    fract += 1;
  }
}

int IMDecimal::getDecimalPlaces(const int value) {
  int places = 0;

  for (int i = 1; value / i != 0; i *= 10, places++);

  return places;
}

float IMDecimal::getFloat() {
  float result = (1.0 * fract) / (1.0 * precision);

  result += 1.0 * whole;
  return result;
}

