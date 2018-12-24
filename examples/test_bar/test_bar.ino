#include <Wire.h>
#include <SFE_BMP180.h>
#include <DS3231.h>

DS3231 clock;
RTCDateTime dt;
//#include <InfiniteMoonshine.h>

const int8_t INFO_LOG     = 0;
const int8_t WARNING_LOG  = 1;
const int8_t ERROR_LOG    = 2;

const char BAROMETER_RESOLUTION = 1;
const float MIN_PRESSURE = 650;

SFE_BMP180 presSensor;

void setup() {
  clock.begin();
  /*float pres;
  unsigned long temp;
  IMDecimal tableTemp;
  
  initLog();
  temp = millis();
  initPresSensor();
  logInfo("Barometer init time "+String(millis() - temp)+" ms");
  temp = millis();
  pres = getPres();
  logInfo("Barometer measurement time "+String(millis() - temp)+" ms");
  logInfo("Pressure value is "+String(pres));
  tableTemp = getTableTemp(pres);
  logInfo("Ethanol boiling temperature "+String(tableTemp.getFloat()));
  */
  Serial.println(getTimeStamp());
  unsigned long timer = millis();
  double T, P;
  char result;

  Serial.begin(9600);
  presSensor.begin();
  Serial.println("Barometer init time "+String(millis() - timer)+" ms");
  timer = millis();
  
  result = presSensor.startTemperature();
  delay(result);
  presSensor.getTemperature(T);
  result = presSensor.startPressure(BAROMETER_RESOLUTION);
  delay(result);
  //Serial.println("delay temp "+String(result, DEC));
  
  //
  //Serial.println("delay pres "+String(result, DEC));
  //delay(result);
  Serial.println("request time "+String(millis() - timer)+" ms");
  timer = millis();

  presSensor.getPressure(P, T);
  Serial.println("receive time "+String(millis() - timer)+" ms");
  
  Serial.println("envTemp "+String(T));
  Serial.println("pres "+String(P*0.75));
  
  //Serial.println("pres "+String(getPres()));
  //Serial.println("receive time "+String(millis() - timer)+" ms");

  //float f = (float) T;

  //Serial.println(String(f));
  Serial.println(getTimeStamp());
}

void loop() {
  // put your main code here, to run repeatedly:

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

bool initPresSensor() {
  return presSensor.begin();
}

void initLog() {
  Serial.begin(9600);
}

float getPres() {
  double T = 0;
  double P = 0;
  char result = presSensor.startTemperature();

  if (result) {
    logInfo("Barometer temperature measurement time "+String(result, DEC));
    delay(result);
    result = presSensor.getTemperature(T);

    if (result) {
      logInfo("Barometer temperature value "+String(T));
      result = presSensor.startPressure(BAROMETER_RESOLUTION);

      if (result) {
        logInfo("Barometer pressure measurement time "+String(result, DEC));
        delay(result);
        result = presSensor.getPressure(P, T);

        if (!result) {
          logError("Barometer failed to retrieve pressure.");
        }
      } else {
        logError("Barometer failed to start pressure measurement.");
      }
    } else {
      logError("Barometer failed to retrieve temperature.");
    }
  } else {
    logError("Barometer failed to start temperature measurement.");
  }
  return P * 3 / 4;
}

String getTimeStamp() {
  dt = clock.getDateTime();
  String out = String(dt.year);
  out += "-" + String(dt.month / 10) + String(dt.month % 10);
  out += "-" + String(dt.day / 10) + String(dt.day % 10);
  out += " " + String(dt.hour / 10) + String(dt.hour % 10);
  out += ":" + String(dt.minute / 10) + String(dt.minute % 10);
  out += ":" + String(dt.second / 10) + String(dt.second % 10);
  return out;
}
/*
IMDecimal getTableTemp(float pressure) {
  if (pressure < MIN_PRESSURE) {
    logError("Incorrect pressure value "+String(pressure));
    return IMDecimal();
  }
  return IMDecimal(0.038*pressure + 49.27);
}
*/
