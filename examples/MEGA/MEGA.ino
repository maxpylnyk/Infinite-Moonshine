#include <IMMega.h>

IMMega mega;

void setup() {
  //add check timeout
  Serial.begin(9600);
  Serial.println("debug started");
  if (mega.init()) {
    mega.debug();
    Serial.println("debug finished");
  } else {
    Serial.println("init failure");
  }
}

void loop() {

}

ISR(SPI_STC_vect) {
  mega.interruptRoutine();
}
/*
void readData() {
  //search and run master commands from array
}

void writeData() {
  //collect data into array
  dataIndex = 0;
}
*/