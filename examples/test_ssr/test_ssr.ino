#include "IMHeater.h"

#define SSR_PIN 3

void setup() {
  pinMode(SSR_PIN, OUTPUT);
  analogWrite(SSR_PIN, 255);
  //digitalWrite(SSR_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}
