#include <Time.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MQ3.h>
#include <Wire.h>

#include <SFE_BMP180.h>

#define THERMOMETERS_PIN        0 //digital
#define BAROMETER_CLOCK_PIN     21
#define BAROMETER_DATA_PIN      20 
#define ALCOHOL_METER_HEATER_PIN 0 //digital with resistor
#define ALCOHOL_METER_DATA_PIN  0 //analog
#define RELAY_PIN               0 //pwm analog

enum {
  STAND_BY_STATE = 0,
  INIT_STATE     = 1,
  STAB_STATE     = 2,
  HEAD_STATE     = 3,
  PRE_BODY_STATE = 4,
  BODY_STATE     = 5,
  PRE_TAIL_STATE = 6,
  ERROR_STATE   = -1
};

enum {
  INFO_LOG       = 0,
  WARNING_LOG    = 1,
  ERROR_LOG      = 2
};

const uint8_t THERMOMETERS_COUNT = 3;
const uint8_t THERMOMETER_RESOLUTION = 12;
const char BAROMETER_RESOLUTION = 1;

const int8_t STEAM_THERMOMETER_INDEX = 0;  //find out
const int8_t WATER_THERMOMETER_INDEX = 1;
const int8_t PIPE_THERMOMETER_INDEX  = 2;

const int OPEN_OUT_TAP      = 0;  //calibrate
const int CLOSED_OUT_TAP    = 0;
const int OPEN_RETURN_TAP   = 0;
const int CLOSED_RETURN_TAP = 0;
const int OPEN_WATER_TAP    = 0;
const int CLOSED_WATER_TAP  = 0;
const int HEAD_OUT_TAP      = 100; //read from file
const int BODY_OUT_TAP      = 550; //read from file

const int8_t POWER_OFF = 0;
const int8_t MIN_POWER = 0; //read from file
const int8_t MAX_POWER = 255;

const int8_t STAB_SAMPLE_COUNT = 3;
const int8_t HEAD_SAMPLE_COUNT = 10;

const float MIN_PRESSURE = 650;

const float STEAM_TEMP_CORRECTION = 0;//calibrate
const float WATER_TEMP_CORRECTION = 0;
const float PIPE_TEMP_CORRECTION  = 0;

bool stateInited = false;
bool malfunction = false;
int8_t currentState = STAND_BY_STATE;

uint8_t heatPower = 0;
uint8_t heatAdjStep = 0;//from file

float srcVol = 0;

int outTapSpeed = 0;
int returnTapSpeed = 0;
int waterTapSpeed = 0;
int refluxRatio = 0;

float controlTemp = 0;

const unsigned long DELAY_TIME      =       3 * 1000;
const unsigned long INIT_CHECKPOINT =      20 * 1000;
const unsigned long STAB_CHECKPOINT =  3 * 60 * 1000;
const unsigned long HEAD_CHECKPOINT =  1 * 60 * 1000;
const unsigned long LOG_CHECKPOINT  = 60 * 60 * 1000;

const unsigned long ALCOHOL_METERING_DELAY = 1000;

unsigned long elapsedTime = 0;
unsigned long estimatedTime = 0;
unsigned long checkpointTime = 0;

float tempArray[10];

OneWire wire(THERMOMETERS_PIN);
DallasTemperature tempSensors(&wire);
DeviceAddress tempAddress[THERMOMETERS_COUNT];
MQ3 alcSensor(ALCOHOL_METER_DATA_PIN, ALCOHOL_METER_HEATER_PIN);
SFE_BMP180 presSensor;

void setup() {
  initTempSensors();
  initAlcSensor();
  initPresSensor();
}

void loop() {
  switch(getCurrentState()) {
    case STAND_BY_STATE:
      standByLoop();
      break;
    case INIT_STATE:
      initLoop();
      break;
    case STAB_STATE:
      stabLoop();
      break;
    case HEAD_STATE:
      headLoop();
      break;
    case PRE_BODY_STATE:
      preBodyLoop();
      break;
    case BODY_STATE:
      bodyLoop();
      break;
    case PRE_TAIL_STATE:
      preTailLoop();
      break;
    case ERROR_STATE:
      errorLoop();
      break;
    default:
      logError("Incorrect state "+String(getCurrentState())+". Standing by.");
      setCurrentState(STAND_BY_STATE);
  }
  if (isProperOperation()) {
    delay(DELAY_TIME);
    elapsedTime += DELAY_TIME;
  } else {
    setCurrentState(ERROR_STATE);
    elapsedTime += emergencyShutdown();
  }
}

int8_t getCurrentState() {
  return currentState;
}

void setCurrentState(int8_t state) {
  currentState = state;
}

bool isProperOperation() {
  /*ask overflow level*/
  return !malfunction;
}

void changeState() {
  setCurrentState(getCurrentState() + 1);
  stateInited = false;
}

void standByLoop() {
  if (!stateInited) {
    setHeatPower(POWER_OFF);
    logInfo("Standing by.");
    stateInited = true;
  }
}

void initLoop() {
  /*  
   * 
   */
  if (!stateInited) {
    setHeatPower(MAX_POWER);
    setOutTap(CLOSED_OUT_TAP);
    setReturnTap(OPEN_RETURN_TAP);
    setWaterTap(OPEN_WATER_TAP);
    logInfo("Starting rectification");
    elapsedTime = 0;
    checkpointTime = elapsedTime;
    stateInited = true;
  }
  if (elapsedTime-checkpointTime < INIT_CHECKPOINT) {
    return;
  }  
  checkpointTime = elapsedTime;
    /*open cooling tap when temp rises*/
    /*reach hi hlevel to switch state*/
//  if (getSteamTemp() > MIN_STEAM_TEMP) {
    changeState();
 // }
}

void stabLoop() {
  if (!stateInited) {
    setHeatPower(MIN_POWER);
    setWaterTap(OPEN_WATER_TAP);
    stateInited = true;
  }
  if (elapsedTime-checkpointTime < STAB_CHECKPOINT) {
    return;
  }  
  checkpointTime = elapsedTime;
  /*control power and flegma levels*/
  if (checkTempStability(STAB_SAMPLE_COUNT)) {
    changeState();
  }
}

void headLoop() {
  if (!stateInited) {
    
  }
  /*temp is jumping -> reduce cooling speed, 100 ml/H for start.
  cooling temp 50 deg
  alc meter shows next state
  wait and flush*/
}

void preBodyLoop() {
  /*close out tap, wait for temp stability.
  it'll be 0.1-0.2 deg higher. memorize value 'controlTemp'.
  change receiving container*/
}

void bodyLoop() {
  /*open out tap. if temp rises 0.1 deg, close tap and wait.
  recheck controlTemp each hour. close out tap, wait 10 min.
  pipeTemp affects out speed*/
}

void preTailLoop() {
  /*2/3 temp rises, lower heat and output, rise rfratio.
  make stab pauses. if temp doesn't fall -> finish*/
}

void errorLoop() {
  /*flicker led*/
}

void logEvent(String message, int8_t level) {
  /*get time and level, new line after each record*/
}

void logInfo(String message) {
  logEvent(message, INFO_LOG);
}

void logError(String message) {
  logEvent(message, ERROR_LOG);
}

void setHeatPower(uint8_t heat) {
  int percent = 100 * (heat / MAX_POWER);
  logInfo("Setting heat to "+String(heat)+" ("+String(percent)+"%)");
  heatPower = heat;
  analogWrite(RELAY_PIN, heat);
}

int8_t getPower() {
  return heatPower;
}

float getTableTemp(float pressure) {
  if (pressure < MIN_PRESSURE) {
    logError("Incorrect pressure value "+String(pressure));
    return 0;
  }
  return 0.038*pressure + 49.27;
}

float getTemp(int8_t index) {
  if (tempSensors.requestTemperaturesByAddress(tempAddress[index])) {
    return tempSensors.getTempC(tempAddress[index]);
  }
  return 0;
}

float getSteamTemp() {
  return getTemp(STEAM_THERMOMETER_INDEX);
}

float getWaterTemp() {
  return getTemp(WATER_THERMOMETER_INDEX);
}

float getPipeTemp() {
  return getTemp(PIPE_THERMOMETER_INDEX);
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

float getDelta() {
  return getSteamTemp() - getTableTemp(getPres());
}

int8_t mlH2Steps(int8_t mlH) {
  return 0;
}

bool setOutTap(int8_t mlH) {
  outTapSpeed = mlH;
  /*set motor steps with correctives*/
  return false;
}

bool setReturnTap(int8_t mlH) {
  returnTapSpeed = mlH;
  /*set motor steps with correctives*/
  return false;
}

bool setWaterTap(int8_t mlH) {
  waterTapSpeed = mlH;
  
  /*set motor steps with correctives*/
  return false;
}

int8_t getOutTapSpeed() {
  return outTapSpeed;
}

int8_t getReturnTapSpeed() {
  return returnTapSpeed;
}

int8_t getWaterTapSpeed() {
  return waterTapSpeed;
}

float getRefluxRatio() {
  return getReturnTapSpeed() / getOutTapSpeed();
}

bool checkTempStability(int8_t n) {
  bool equal = true;
  int8_t last = n - 1;
  
  for (int8_t i = 0, j = 1; i < last; i++, j++) {
    tempArray[i] = tempArray[j];
  }
  tempArray[last] = getSteamTemp();

  for (int8_t i = 0, j = 1; i < last; i++, j++) {
    equal &= tempArray[i] == tempArray[j];
  }
  return equal;
}

unsigned long emergencyShutdown() {
  int8_t prevPower = getPower();
  int8_t prevOutSpeed = getOutTapSpeed();
  int8_t prevReturnSpeed = getReturnTapSpeed();
  unsigned long delayTime = 0;
  
  setHeatPower(POWER_OFF);
  setOutTap(OPEN_OUT_TAP);
  setReturnTap(OPEN_RETURN_TAP);
  logError("Emergency shutdown.");

  /*flush and cool, count time
  return to normal operation*/
  return delayTime;
}

bool changeContainer() {
  return false;
}

bool initTempSensors() {
  bool sensorsReady = true;
  uint8_t deviceCount;
  
  tempSensors.begin();
  deviceCount = tempSensors.getDeviceCount();

  if (deviceCount < THERMOMETERS_COUNT) {
    logInfo(String(deviceCount, DEC)+" thermometers online.");
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

bool initAlcSensor() {
  //heat fo 60 sec, calibrate, turn off
}
/*
float getAlcLevel() {
  int level;
  
  digitalWrite(ALCOHOL_METER_HEATER_PIN, HIGH);
  level = analogRead(ALCOHOL_METER_DATA_PIN);
  delay(ALCOHOL_METERING_DELAY);
  digitalWrite(ALCOHOL_METER_HEATER_PIN, LOW);
  return 0.05 + 9.95 * level / 1024.0
}
*/

bool initPresSensor() {
  return presSensor.begin();
}
