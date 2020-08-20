#include "other/IMErrors.h"

IMErrors::IMErrors() {}

bool IMErrors::add(uint8_t error) {
  if (contains(error)) {
    return false;
  }
  errors[count] = error;
  count += 1;
  return true;
}

void IMErrors::clear() {
  for (uint8_t i = 0; i < count; i++) {
    errors[i] = 0;
  }
  count = 0;
}

bool IMErrors::contains(uint8_t error) {
  for (uint8_t i = 0; i < count; i++) {
    if (errors[i] == error) {
      return true;
    }
  }
  return false;
}

bool IMErrors::remove(uint8_t error) {
  bool found = false;

  for (uint8_t i = 0, j = 1; i < count; i++, j++) {
    found |= errors[i] == error;

    if (found) {
      errors[i] = errors[j];
    }
  }
  if (found) {
    count -= 1;
  }
  return found;
}

bool IMErrors::isEmpty() {
  return count == 0;
}

uint8_t IMErrors::getCount() {
  return count;
}

uint8_t IMErrors::get(uint8_t index) {
  if (index >= count) {
    return 0;
  }
  return errors[index];
}
