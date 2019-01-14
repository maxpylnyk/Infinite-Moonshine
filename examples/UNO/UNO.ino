#include <IMUno.h>

IMUno uno;

void setup() {
  //introduce waitdog. reload if timeout reached.
  if (uno.init()) {
    uno.debug();
  } else {
    Serial.println("init failure");
  }
}

void loop() {

}
