#include "IMNano.h"

IMNano::IMNano() : InfiniteMoonshine(NANO_RST_PIN) {}

bool IMNano::init() {
  bool result = true;
  pinMode(LED_BUILTIN, OUTPUT);
  initWatchdog();

  port = &Serial;
  port->begin(serialSpeed);
  sendCallsign();
  return result;
}

void IMNano::loop() {
  restartWatchdog();

  if (callsignReceived) {
    if (millis() - responseTime >= callsignTimeout) {
      sendCallsign();
      
      digitalWrite(LED_BUILTIN, HIGH);
      delay(blinkDelay);
      digitalWrite(LED_BUILTIN, LOW);
    }
  } else {
    if (waitingTimer.getElapsedTime() >= responseTimeLimit) {
      if (connectionAttempts > attemptsLimit) {
        if (restartAttempts > attemptsLimit) {
          digitalWrite(LED_BUILTIN, HIGH);
          delay(blinkDelay);
          digitalWrite(LED_BUILTIN, LOW);
          delay(blinkDelay); 
        } else {
          restartAttempts += 1;
          restartOther();
        }
      } else {
        connectionAttempts += 1;
        sendCallsign();
        
        digitalWrite(LED_BUILTIN, HIGH);
        delay(blinkDelay);
        digitalWrite(LED_BUILTIN, LOW);
      }
    } else {
      //waiting for callsign
    }
  }
}

void IMNano::debug() {

}

void IMNano::receiveCallsign() {
  char answer = port->read();

  switch(answer) {
    case initSign:
      if (callsign == onlineSign) {
        errors.add(IMError::MEGA_BLACKOUT);
        sendData();
      }
      callsignReceived = true;
      responseTime = millis();
      connectionAttempts = 0;
      waitingTimer.stop();
      break;
    case onlineSign:
      if (callsign == initSign) {

      }
      callsignReceived = true;
      responseTime = millis();
      connectionAttempts = 0;
      waitingTimer.stop();
      break;
    case restartSign:
      thisRestarted = true;
    case dataSign:
      receiveData();
      callsignReceived = true;
      responseTime = millis();
      connectionAttempts = 0;
      waitingTimer.stop();
      break;
    default:
      errors.add(IMError::TRANSMISSION_CORRUPTED);
      //repeat transfer, attempts += 1; then if fails -> error
  }
}

void IMNano::sendData() {
  queue = String(restartSign);
  addToQueue(LogIndex::SESSION_NAME, String(session.getName()));
  addToQueue(LogIndex::START_TIME, String(session.getStartTime()));
  addToQueue(LogIndex::UPD_TIME, String(updTime));
  addToQueue(LogIndex::STATE, String(session.getState()));
  addToQueue(LogIndex::PAUSE, String(session.isPaused()));
  addToQueue(LogIndex::SRC_VOL, String(session.getSrcVol()));
  addToQueue(LogIndex::SRC_TYPE, String(session.getSrcType()));
  addToQueue(LogIndex::WATER_SPEED, String(session.getWaterSpeed()));
  addToQueue(LogIndex::WATER_ADJ, String(session.getWaterAdj()));
  addToQueue(LogIndex::SW, String(session.getSwitchPos()));
  addToQueue(LogIndex::HEAT, String(session.getHeatPwr()));
  addToQueue(LogIndex::HEAT_ADJ, String(session.getHeatAdj()));
  addToQueue(LogIndex::RF, String(session.getRefluxRatio()));
  addToQueue(LogIndex::EXT_SPEED, String(session.getExtSpeed()));
  addToQueue(LogIndex::REF_SPEED, String(session.getRefluxSpeed()));
  addToQueue(LogIndex::EXT_ADJ, String(session.getExtAdj()));
  addToQueue(LogIndex::HEAD_OUT_ML, String(session.getHeadOutML()));
  addToQueue(LogIndex::BODY_OUT_ML, String(session.getBodyOutML()));
  addToQueue(LogIndex::USED_WATER_L, String(session.getUsedWaterL()));
  addToQueue(LogIndex::USED_POWER_KW, String(session.getUsedPowerKW()));
  endQueue();
  debugText = "";
}

void IMNano::receiveData() {
  while (port->available()) {
    int index = port->parseInt();

    switch(index) {
      case LogIndex::SESSION_NAME :
        session.setName(port->parseInt());
        break;
      case LogIndex::START_TIME :
        session.setStartTime(port->parseInt());
        break;
      case LogIndex::UPD_TIME :
        updTime = port->parseInt();
        break;
      case LogIndex::STATE :
        session.setState(port->parseInt());
        break;
      case LogIndex::PAUSE :
        session.setPause(port->parseInt());
        break;
      case LogIndex::SRC_VOL :
        session.setSrcVol(port->parseInt());
        break;
      case LogIndex::SRC_TYPE :
        session.setSrcType(port->parseInt());
        break;
      case LogIndex::ERROR_CODES :
        errors.add(port->parseInt());
        break;
      case LogIndex::HYDRO_LEVEL :
        session.setHydroLvl(port->parseInt());
        break;
      case LogIndex::ALC_LEVEL :
        session.setAlcLvl(port->parseInt());
        break;
      case LogIndex::STEAM_TEMP :
        session.setSteamTemp(port->parseFloat());
        break;
      case LogIndex::COND_TEMP :
        session.setCondTemp(port->parseFloat());
        break;
      case LogIndex::PIPE_TEMP :
        session.setPipeTemp(port->parseFloat());
        break;
      case LogIndex::WATER_SPEED :
        session.setWaterSpeed(port->parseInt());
        break;
      case LogIndex::WATER_ADJ :
        session.setWaterAdj(port->parseInt());
        break;
      case LogIndex::SW :
        session.setSwitchPos(port->parseInt());
        break;
      case LogIndex::HEAT :
        session.setHeatPwr(port->parseInt());
        break;
      case LogIndex::HEAT_ADJ :
        session.setHeatAdj(port->parseInt());
        break;
      case LogIndex::RF :
        session.setRefluxRatio(port->parseInt());
        break;
      case LogIndex::EXT_SPEED :
        session.setExtSpeed(port->parseInt());
        break;
      case LogIndex::REF_SPEED :
        session.setRefluxSpeed(port->parseInt());
        break;
      case LogIndex::EXT_ADJ :
        session.setExtAdj(port->parseInt());
        break;
      case LogIndex::HEAD_OUT_ML :
        session.setHeadOutML(port->parseInt());
        break;
      case LogIndex::BODY_OUT_ML :
        session.setBodyOutML(port->parseInt());
        break;
      case LogIndex::USED_WATER_L :
        session.setUsedWaterL(port->parseFloat());
        break;
      case LogIndex::USED_POWER_KW :
        session.setUsedPowerKW(port->parseFloat());
        break;
      case endOfTransmission:
        if (initialize) {
          initialize = false;
        }
        break;
    }
  }
}
