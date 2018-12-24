int8_t analogPin = A0;
int8_t digitalPin = 2;
int8_t powerPin = 3;

void setup() {
  Serial.begin(9600);
  pinMode(powerPin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

bool soilIsDry() {
  bool isDry;
  
  digitalWrite(powerPin, HIGH);
  delay(1000);
  isDry = digitalRead(digitalPin);
  digitalWrite(powerPin, LOW);
  return isDry;
}

