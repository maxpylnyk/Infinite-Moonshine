#include "IMInfoButton.h"

IMInfoButton::IMInfoButton(IMPane * owner, IMRect place, uint16_t color) : IMButton(owner, place, color) {}

void IMInfoButton::draw() {
  
}

void IMInfoButton::action() {
  Serial.println("info pressed");
}