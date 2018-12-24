#define ALC_DATA_PIN A1
#define ALC_HEAT_PIN 53

#define MQ3_RO_IN_CLEAR_AIR     60.0
#define MQ3_RL_BOARD            200.0
#define ADC_BIT             10
#define ADC_VALUE_MAX       pow(2, ADC_BIT)
#define OPERATING_VOLTAGE   5.0
#define SCALE_A           -0.66
#define SCALE_B           -0.62

#define DELAY  60000
float r0;

void setup() {
  unsigned long timer = millis();
  Serial.begin(9600);
  pinMode(ALC_HEAT_PIN, OUTPUT);
  requestValue();
  delay(DELAY);
  Serial.println("delay passed");
  r0 = getRs() / MQ3_RO_IN_CLEAR_AIR;
  Serial.println("r0 "+String(r0));
  Serial.println("init time "+String(millis()-timer)+" ms");
  delay(DELAY);
}

void loop() {
  unsigned long timer = millis();
  requestValue();
  delay(DELAY);
  Serial.println("request time "+String(millis()-timer)+" ms");
  timer = millis();
  Serial.println("Alcohol "+String(getMgL())+" mg/L");
  Serial.println("receive time "+String(millis()-timer)+" ms");
  delay(DELAY);
}

void requestValue() {
  Serial.println("requesting value");
  digitalWrite(ALC_HEAT_PIN, HIGH);
  Serial.println("power on");
}

float getRs() {
  Serial.println("reading data");
  int data = analogRead(ALC_DATA_PIN);
  float volt;
  Serial.println("raw data "+String(data));
  digitalWrite(ALC_HEAT_PIN, LOW);
  volt = data * (OPERATING_VOLTAGE / ADC_VALUE_MAX);
  return (OPERATING_VOLTAGE - volt) / volt * MQ3_RL_BOARD;
}

float getMgL() {
  float ratio = getRs() / r0;

  return exp((log(ratio) - SCALE_B) / SCALE_A);
}

