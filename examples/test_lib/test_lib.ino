#include "IMSync.h"

void setup() {
  IMSync sync(2);
  int16_t i = -31756;
  float f = 751.49587;
  uint32_t s = 20190107;
  uint8_t bytes[4];

  Serial.begin(9600);
  //Serial.println(String(i));
  //Serial.println(String(f));
  /*
  sync.toArray(i, bytes);
  Serial.println(String(bytes[0], BIN)+" first received byte");
  Serial.println(String(bytes[1], BIN)+" second received byte");

  Serial.println(String(sync.toShort(bytes), DEC)+" original value");

  sync.toArray(f, bytes);

  Serial.println(String(sync.toFloat(bytes), DEC)+" original value");
  //temp = *(bytes+1);
  //Serial.println(String(temp, BIN)+" second received byte");
  
  //Serial.println(String(bytes+1));

  //Serial.println(String(sync.toShort(sync.toArray(i))));
  //Serial.println(String(sync.toFloat(sync.toArray(f))));
  */
  sync.toArray(s, bytes);
  Serial.println(String(sync.toUInt(bytes)));
}

void loop() {
  // put your main code here, to run repeatedly:

}
