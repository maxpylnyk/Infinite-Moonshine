#define THERMOMETERS_PIN 51

#include <InfiniteMoonshine.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int8_t INFO_LOG     = 0;
const int8_t WARNING_LOG  = 1;
const int8_t ERROR_LOG    = 2;

const uint8_t THERMOMETERS_COUNT = 4;
const uint8_t THERMOMETER_RESOLUTION = 12;

OneWire wire(THERMOMETERS_PIN);
DallasTemperature tempSensors(&wire);
DeviceAddress tempAddress[THERMOMETERS_COUNT];
float tempValues[THERMOMETERS_COUNT];

void setup() {
  float temp;
  unsigned long timer = millis();
  unsigned long receiveTimer;
  initLog();
  initTempSensors();
  Serial.println("init time "+String(millis() - timer)+" ms");
  timer = millis();
  /*
  temp = getTemp(THERMOMETER_INDEX);
  Serial.println("measure time "+String(millis() - timer)+" ms");
  Serial.println("temp "+String(temp, DEC));
  Serial.print("Device address ");
  printAddress(tempAddress[THERMOMETER_INDEX]);
  Serial.println();
  */
  timer = millis();
  tempSensors.requestTemperatures();
    Serial.println("request time "+String(millis() - timer)+" ms");
    timer = millis();

    for (int i = 0; i < THERMOMETERS_COUNT; i++) {
      receiveTimer = millis();

      tempValues[i] = tempSensors.getTempC(tempAddress[i]);
      Serial.print ("trm "+String(i+1)+" value "+String(tempValues[i], DEC));
      Serial.print(" addr ");
      printAddress(tempAddress[i]);
      Serial.println(" receive time "+String(millis()-receiveTimer)+" ms");
    }
    Serial.println("overall receive time "+String(millis()-timer)+" ms");
}

void loop() {
  // put your main code here, to run repeatedly:

}

bool initTempSensors() {
  bool sensorsReady = true;
  uint8_t deviceCount;
  
  tempSensors.begin();
  deviceCount = tempSensors.getDeviceCount();

  if (deviceCount < THERMOMETERS_COUNT) {
    logInfo(String(deviceCount)+" thermometers online.");
    sensorsReady = false;
  } else {
    for (int i = 0; i < deviceCount; i++) {
      bool sensorOnline = tempSensors.getAddress(tempAddress[i], i);

      if (sensorOnline) {
        tempSensors.setResolution(tempAddress[i], THERMOMETER_RESOLUTION);
      }
      sensorsReady &= sensorOnline;
    }
  }
  return sensorsReady;
}

float getTemp(int8_t index) {
  float result;
  unsigned long temp = millis();
  if (tempSensors.requestTemperaturesByAddress(tempAddress[index])) {
    Serial.println("request time "+String(millis() - temp)+" ms");
    temp = millis();
    result = tempSensors.getTempC(tempAddress[index]);
    Serial.println("receive time "+String(millis() - temp)+" ms");
    return result;
  }
  return 0;
}

void logEvent(String message, int8_t level) {
  if (level == INFO_LOG) {
    Serial.print("INFO: ");
  } else {
    Serial.print("ERROR: ");
  }
  Serial.println(message);
}

void logInfo(String message) {
  logEvent(message, INFO_LOG);
}

void logError(String message) {
  logEvent(message, ERROR_LOG);
}

void initLog() {
  Serial.begin(9600);
}

void printAddress(DeviceAddress deviceAddress){
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
