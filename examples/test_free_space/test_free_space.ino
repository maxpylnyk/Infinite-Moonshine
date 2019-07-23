#include <SdFat.h>
SdFat sd;
const uint8_t csPin = SS;

void setup() {
  Serial.begin(9600);
  if (!sd.begin(csPin)) sd.initErrorHalt();
  uint32_t freeKB = sd.vol()->freeClusterCount();
  freeKB *= sd.vol()->blocksPerCluster()/2;
  Serial.print("Free space KB: ");
  Serial.println(freeKB);
}
void loop() {}
