#include "IMTouchScreen.h"

IMTouchScreen ts;

void setup() {
  Serial.begin(9600);
  ts.init();
}

void loop() {
  ts.handleTouch();
}
