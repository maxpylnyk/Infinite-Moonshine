#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

void setup() {
  Serial.begin(9600);
  /*
  attachInterrupt(digitalPinToInterrupt(IN2), port2Signal, RISING);
  attachInterrupt(digitalPinToInterrupt(IN3), port3Signal, RISING);
  attachInterrupt(digitalPinToInterrupt(IN4), port4Signal, RISING);
  attachInterrupt(digitalPinToInterrupt(IN5), port5Signal, RISING);
  attachInterrupt(digitalPinToInterrupt(IN6), port6Signal, RISING);
  attachInterrupt(digitalPinToInterrupt(IN7), port7Signal, RISING);
  */
}

void loop() {
  if (digitalRead(PIN4)) {
    port4Signal();
  }
}

void port2Signal() {
  Serial.println("port 2 signal HIGH");
}

void port3Signal() {
  Serial.println("port 3 signal HIGH");
}

void port4Signal() {
  Serial.println("port 4 signal HIGH");
}

void port5Signal() {
  Serial.println("port 5 signal HIGH");
}

void port6Signal() {
  Serial.println("port 6 signal HIGH");
}

void port7Signal() {
  Serial.println("port 7 signal HIGH");
}
