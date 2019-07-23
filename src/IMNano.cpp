#include "IMNano.h"

IMNano::IMNano() : InfiniteMoonshine(PinMap::NANO_RST) {}

bool IMNano::init() {
  bool result = true;

  initWatchdog();
  port = &Serial;
  port->begin(serialSpeed);
  /*
  logger.setErrorList(&errors);
  result &= logger.init();

  if (!timer.init()) {
    errors.add(IMError::NO_RTC);
    result = false;
  }
  if (!bar.init()) {
    errors.add(IMError::NO_BAR);
    result = false;
  }
  */
  sendCallsign();
  return result;
}

void IMNano::loop() {
  //refresh ui and wait for user input
  //send callsigns
  //check timeouts
  //read env data
  //check and handle errors. show error messages.
  //if error handled, wait to log, then remove from list
  //restart wtd
  //log
}

void IMNano::debug() {
  //fill array and transfer
}

void IMNano::receiveCallsign() {
  char answer = port->read();
  //write response time
  switch(answer) {
    case initSign:
      if (callsign == initSign) {
        readPrevLog();
        sendData();
      } else if (callsign == onlineSign) {
        errors.add(IMError::MEGA_BLACKOUT);
        sendData();
        //blackout handled
      }
      break;
    case onlineSign:
      if (callsign == initSign) {
        //errors.add(IMError::UNO_BLACKOUT);
        //receive full data >
      }
      break;
    case restartSign:
      thisRestarted = true;
      receiveData();
      logRestart();
      break;
    case dataSign:
      receiveData();//write timeout
      break;
    default:
      errors.add(IMError::TRANSMISSION_CORRUPTED);
  }
}

void IMNano::readPrevLog() {
  //find last log, read end. if @ finished -> stby
  //                         if not -> load checkpoint and resumePrevSession = true;
  //calculate timeout and water usage during blackout
  //if log ended with error -> check if it still present
  //if no log found -> stby
  //fills queue with commands
}

void IMNano::logRestart() {
  if (thisRestarted) {
    logRestart(Board::NANO);
    thisRestarted = false;
  }
  if (otherRestarted) {
    logRestart(Board::MEGA);
    otherRestarted = false;
  }
}

void IMNano::logRestart(Board board) {
  String rec = String(restartSign);

  rec += " ";
  rec += timer.getLogStamp();
  rec += " ";
  rec += String(board);

  //logger.println(rec);
}

void IMNano::logData() {
  //no log when paused
}

void IMNano::sendData() {
  if (otherRestarted) {
    callsign = restartSign;
  } else {
    callsign = dataSign;
  }
  queue = String(callsign);

  if (errors.contains(IMError::MEGA_BLACKOUT) || otherRestarted || resumePrevSession) {
    addToQueue(LogIndex::SESSION_NAME, String(getSessionName()));
    addToQueue(LogIndex::STATE, String(getStateIndex()));
    addToQueue(LogIndex::PAUSE, String(isPaused()));
    addToQueue(LogIndex::COND_MTR, String(condMtrPos));
    addToQueue(LogIndex::COND_MTR_ADJ, String(condMtrAdj));
    addToQueue(LogIndex::SW, String(switchPosition));
    addToQueue(LogIndex::HEAT, String(heatPower));
    addToQueue(LogIndex::HEAT_ADJ, String(heatAdjStep));
    addToQueue(LogIndex::RF, String(refluxRatio));
    addToQueue(LogIndex::OUT_MTR, String(outMtrPos));
    addToQueue(LogIndex::RET_MTR, String(retMtrPos));
    addToQueue(LogIndex::EXT_ADJ, String(extMtrAdj));
    addToQueue(LogIndex::ENV_TEMP, String(envTemp));
    addToQueue(LogIndex::PRESSURE, String(pressure));
    endQueue();
    logRestart();
  }



  //cmd sends by one on press action

}

void IMNano::receiveData() {
  while (port->available()) {
    int index = port->parseInt();

    switch(index) {
      case LogIndex::SESSION_NAME :
        setSessionName(port->parseInt());
        break;
      case LogIndex::STATE :
        setStateIndex(port->parseInt());
        break;
      case LogIndex::PAUSE :
        setPause(port->parseInt());
        break;
      case LogIndex::ERROR_CODES :
        errors.add(port->parseInt());
        break;
      case LogIndex::HYDRO_LEVEL :
        hydroLevel = port->parseInt();
        break;
      case LogIndex::ALC_LEVEL :
        alcLevel = port->parseInt();
        break;
      case LogIndex::STEAM_TEMP :
        steamTemp = port->parseFloat();
        break;
      case LogIndex::COND_TEMP :
        condTemp = port->parseFloat();
        break;
      case LogIndex::PIPE_TEMP :
        pipeTemp = port->parseFloat();
        break;
      case LogIndex::COND_MTR :
        condMtrPos = port->parseInt();
        break;
      case LogIndex::COND_MTR_ADJ :
        condMtrAdj = port->parseInt();
        break;
      case LogIndex::SW :
        switchPosition = port->parseInt();
        break;
      case LogIndex::HEAT :
        heatPower = port->parseInt();
        break;
      case LogIndex::HEAT_ADJ :
        heatAdjStep = port->parseInt();
        break;
      case LogIndex::RF :
        refluxRatio = port->parseInt();
        break;
      case LogIndex::OUT_MTR :
        outMtrPos = port->parseInt();
        break;
      case LogIndex::RET_MTR :
        retMtrPos = port->parseInt();
        break;
      case LogIndex::EXT_ADJ :
        extMtrAdj = port->parseInt();
        break;
      case endOfTransmission:
        if (initialize) {
          initialize = false;
        }
        break;
    }
  }
}
