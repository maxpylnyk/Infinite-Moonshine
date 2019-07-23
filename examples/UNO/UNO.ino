#include <IMUno.h>

IMUno uno;

void setup() {
  if (uno.init()) {
    uno.debug();
  }
}

void loop() {
  uno.loop();
}

void serialEvent() {
  uno.receiveCallsign();
}
