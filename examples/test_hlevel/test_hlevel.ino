#define HYDROLEVEL_PIN A1

#include <InfiniteMoonshine.h>

void setup() {
  Serial.begin(9600);
  unsigned long timer = millis();
  int data = analogRead(HYDROLEVEL_PIN);
  int Vin = 5;
  float Vout = 0;
  float buffer;
  float R1 = 2.7;
  float R2 = 0;

  Serial.println("Receiving time "+String(millis() - timer)+" ms");
  Serial.println("Raw data "+String(data));

  buffer = data * Vin;
  Vout = buffer / 1024.0;
  Serial.println("Vout "+String(Vout));

  if (data) {
    buffer = Vin / Vout - 1;
    R2 = R1 * buffer;
    Serial.println("R2 "+String(R2));
  } else {
    Serial.println("R2 inf");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
