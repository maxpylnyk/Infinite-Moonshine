#include "IMThermometers.h"

IMThermometers t;

void setup() {
  t.init();

}

void loop() {
  float steam = t.getSteamTemp();
  Serial.println(String(steam));
  delay(1000);
}
