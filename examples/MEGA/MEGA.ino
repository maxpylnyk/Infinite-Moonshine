#include <IMMega.h>

IMMega mega;

void setup() {
  if (mega.init()) {
    mega.debug();
  } else {
    Serial.println("mega init failure");
  }
}

void loop() {
  mega.loop();
}

void serialEvent1() {
  mega.receiveCallsign();
}
