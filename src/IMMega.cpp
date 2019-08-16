#include "IMMega.h"

IMMega::IMMega() : InfiniteMoonshine(MEGA_RST_PIN) {}

void IMMega::setMasterSPI() {
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);
}

bool IMMega::init() {
  bool result = true;

  timer.start();
  initWatchdog();
  setMasterSPI();

  if (DEBUG_MODE) {
    debugPort = &Serial;
    debugPort->begin(usbSpeed);
  }
  
  debugPort->print("initializing screen.. ");

  if (ui.init()) {
    debugPort->println("done in "+String(timer.check())+" ms");
  } else {
    debugPort->println("failed");
    timer.check();
    result = false;
  }
  
  /*
  debugPort->print("initializing serial interface.. ");
  port = &Serial1;
  port->begin(serialSpeed);
  debugPort->println("done in "+String(timer.check())+" ms");
  
  debugPort->println("waiting for callsign");
  while(!port->available());//if no transmission or delay -> error
  debugPort->println("data transfer complete in "+String(timer.check())+" ms");
  */
  /* 
  debugPort->print("setting state.. ");
  state = &IMStandByState();
  debugPort->println("done in "+String(timer.check())+" ms");
  */
  /* 
  debugPort->print("initializing log.. ");//after receiving data
  log.setErrorList(&errors);

  if (log.init()) {
    debugPort->println("done in "+String(timer.check())+" ms");
  } else {
    debugPort->println("failed");
    timer.check();
    result = false;
  }
  */
  debugPort->print("initializing thermometers.. ");
  trm.setErrorList(&errors);

  if (trm.init()) {
    debugPort->println("done in "+String(timer.check())+" ms");
  } else {
    debugPort->println("failed");
    timer.check();
    result = false;
  }
  
  debugPort->print("initializing hydrolevel.. ");

  if (hlvl.init()) {
    debugPort->println("done in "+String(timer.check())+" ms");
  } else {
    debugPort->println("failed");
    timer.check();
    result = false;
  }
  
  debugPort->print("initializing realtime clock.. ");

  if (timer.init()) {
    debugPort->println("done in "+String(timer.check())+" ms");
  } else {
    errors.add(IMError::NO_RTC);
    debugPort->println("failed");
    timer.check();
    result = false;
  }
  debugPort->print("initializing barometer.. ");

  if (bar.init()) {
    debugPort->println("done in "+String(timer.check())+" ms");
  } else {
    errors.add(IMError::NO_BAR);
    debugPort->println("failed");
    timer.check();
    result = false;
  }
  /* 
  debugPort->print("initializing alcohol sensor.. ");

  if (alc.init()) {
    debugPort->println("done in "+String(timer.check())+" ms");
  } else {
    errors.add(IMError::NO_ALC);
    debugPort->println("failed");
    timer.check();
    result = false;
  }
  */
  //result &= !initialize;
  debugPort->println("initialization done in "+String(timer.stop())+" ms");
  
  if (result) {
    debugPort->println("system is ready to use");
    ui.drawFrontPane();
  } else {
    debugPort->println("system initialization failure");
    printErrors();
    ui.drawErrorsPane(&errors);
  }

  return result;
}

void IMMega::loop() {
  restartWatchdog();
  //check timeouts
  //if timers == 0 -> init and measure
  //check and handle errors (if possible)

  //collect sensors values
  //send data
  //receive commands



  ui.handleTouch();
  /*
  if (millis() - temp >= 3000) {
    debugPort->println(String(millis())+" loop check");
    temp = millis();
  }
  */
  ui.refresh();
}

void IMMega::debug() {
  /*
  timer.start();
  trm.requestData();
  trm.receiveData();

  if (trm.dataReady()) {
    
    debugPort->print("trm ");
    debugPort->print(String(trm.getCondTemp(), DEC));
    debugPort->print(" ");
    debugPort->print(String(timer.check()));
    debugPort->println(" ms");
    
    bar.requestData();
    bar.setEnvTemp(trm.getCondTemp());
    bar.receiveData();

    debugPort->print("bar ");
    debugPort->print(String(bar.getPressure(), DEC));
    debugPort->print(" ");
    debugPort->print(String(timer.check()));
    debugPort->println(" ms");

    debugPort->print("clc ");
    debugPort->println(String(calculateTemp(bar.getPressure()), DEC));

    debugPort->println();
  }
  */
  
  //trm.debug();
  //hlvl.debug();
  //alc.debug();


  //outMtr.loop();
}

void IMMega::receiveCallsign() {
  char message = port->read();

  switch(message) {
    case initSign:
      sendCallsign();

      if (callsign == onlineSign) {
        errors.add(IMError::NANO_BLACKOUT);
        sendData();
      }
      break;
    case onlineSign:
      sendCallsign();
      break;
    case restartSign:
      thisRestarted = true;
    case dataSign:
      receiveData();
      break;
    default:
      errors.add(IMError::TRANSMISSION_CORRUPTED);
      debugPort->print("unknown callsign received: ");
      debugPort->println(message);
  }
}

void IMMega::sendData() {//encapsulate
  if (otherRestarted) {
    callsign = restartSign;
  } else {
    callsign = dataSign;
  }
  queue = String(callsign);

  if (errors.contains(IMError::NANO_BLACKOUT || otherRestarted)) {
    addToQueue(LogIndex::SESSION_NAME, String(getSessionName()));
  }

  for (int i = 0; i < errors.getCount(); i++) {
    addToQueue(LogIndex::ERROR_CODES, String(errors.get(i)));
  }
  errors.clear();

  addToQueue(LogIndex::STATE, String(getStateIndex()));//if changed
  addToQueue(LogIndex::PAUSE, String(isPaused()));
  addToQueue(LogIndex::HYDRO_LEVEL, String(hlvl.getLevel()));
  addToQueue(LogIndex::ALC_LEVEL, String(alc.getLevel()));
  addToQueue(LogIndex::STEAM_TEMP, String(trm.getSteamTemp(), FLOAT_PRECISION));
  addToQueue(LogIndex::COND_TEMP, String(trm.getCondTemp(), FLOAT_PRECISION));
  addToQueue(LogIndex::PIPE_TEMP, String(trm.getPipeTemp(), FLOAT_PRECISION));
  addToQueue(LogIndex::ENV_TEMP, String(trm.getEnvTemp(), FLOAT_PRECISION));
  addToQueue(LogIndex::PRESSURE, String(bar.getPressure()));
  addToQueue(LogIndex::COND_MTR, String(0));
  addToQueue(LogIndex::COND_MTR_ADJ, String(0));
  addToQueue(LogIndex::SW, String(0));
  addToQueue(LogIndex::HEAT, String(heater.getPower()));
  addToQueue(LogIndex::HEAT_ADJ, String(heater.getAdjStep()));
  addToQueue(LogIndex::RF, String(0));
  addToQueue(LogIndex::OUT_MTR, String(0));
  addToQueue(LogIndex::RET_MTR, String(0));
  addToQueue(LogIndex::EXT_ADJ, String(0));
  endQueue();
}

void IMMega::receiveData() {//encapsulate
  while (port->available()) {
    int index = port->parseInt();
    long iTemp;
    float fTemp;

    switch(index) {
      case LogIndex::SESSION_NAME :
        iTemp = port->parseInt();
        debugPort->print("parsed session name ");
        debugPort->println(iTemp);
        setSessionName(iTemp);
        break;
      case LogIndex::STATE :
        iTemp = port->parseInt();
        debugPort->print("parsed status ");
        debugPort->println(iTemp);
        setStateIndex(iTemp);
        break;
      case LogIndex::PAUSE :
        iTemp = port->parseInt();
        debugPort->print("parsed pause ");
        debugPort->println(iTemp);
        setManualPause(iTemp);
        break;
      case LogIndex::ERROR_CODES :
        iTemp = port->parseInt();
        debugPort->print("parsed error code ");
        debugPort->println(iTemp);
        errors.add(iTemp);
        break;
      case LogIndex::HYDRO_LEVEL ://remove
        iTemp = port->parseInt();
        debugPort->print("parsed hydro level ");
        debugPort->println(iTemp);
        break;
      case LogIndex::ALC_LEVEL ://remove
        iTemp = port->parseInt();
        debugPort->print("parsed alcohol level ");
        debugPort->println(iTemp);
        break;
      case LogIndex::STEAM_TEMP ://remove
        fTemp = port->parseFloat();
        debugPort->print("parsed steam temp ");
        debugPort->println(fTemp);
        break;
      case LogIndex::COND_TEMP ://remove
        fTemp = port->parseFloat();
        debugPort->print("parsed cond temp ");
        debugPort->println(fTemp);
        break;
      case LogIndex::PIPE_TEMP ://remove
        fTemp = port->parseFloat();
        debugPort->print("parsed pipe temp ");
        debugPort->println(fTemp);
        break;
      case LogIndex::ENV_TEMP :
        fTemp = port->parseFloat();
        debugPort->print("parsed env temp ");
        debugPort->println(fTemp);
        envTemp = fTemp;
        break;
      case LogIndex::PRESSURE :
        fTemp = port->parseFloat();
        debugPort->print("parsed pressure ");
        debugPort->println(fTemp);
        pressure = fTemp;
        break;
      case LogIndex::COND_MTR ://class
        iTemp = port->parseInt();
        debugPort->print("parsed comd mtr ");
        debugPort->println(iTemp);

        if (initialize) {
          //create object and set itemp as init value
        }
        break;
      case LogIndex::COND_MTR_ADJ ://class
        iTemp = port->parseInt();
        debugPort->print("parsed cond mtr adj ");
        debugPort->println(iTemp);

        if (initialize) {
          //create object and set itemp as init value
        }
        break;
      case LogIndex::SW ://class
        iTemp = port->parseInt();
        debugPort->print("parsed switch position ");
        debugPort->println(iTemp);

        if (initialize) {
          //create object and set itemp as init value
        } else {
          //set object to change value to itemp
        }
        break;
      case LogIndex::HEAT ://class
        iTemp = port->parseInt();
        debugPort->print("parsed heating power ");
        debugPort->println(iTemp);

        if (initialize) {
          //create object and set itemp as init value
        } else {
          //set object to change value to itemp
        }
        break;
      case LogIndex::HEAT_ADJ ://class
        iTemp = port->parseInt();
        debugPort->print("parsed heating adj step ");
        debugPort->println(iTemp);

        if (initialize) {
          //create object and set itemp as init value
        } else {
          //set object to change value to itemp
        }
        break;
      case LogIndex::RF ://class
        iTemp = port->parseInt();
        debugPort->print("parsed reflux ratio ");
        debugPort->println(iTemp);

        if (initialize) {
          //create object and set itemp as init value
        } else {
          //set object to change value to itemp
        }
        break;
      case LogIndex::OUT_MTR ://class
        iTemp = port->parseInt();
        debugPort->print("parsed out mtr ");
        debugPort->println(iTemp);

        if (initialize) {
          //setCurrentPosition
        } else {
          //setTargetPosition
        }
        break;
      case LogIndex::RET_MTR ://class
        iTemp = port->parseInt();
        debugPort->print("parsed ret mtr ");
        debugPort->println(iTemp);

        if (initialize) {
          //create object and set itemp as init value
        } else {
          //set object to change value to itemp
        }
        break;
      case LogIndex::EXT_ADJ ://class
        iTemp = port->parseInt();
        debugPort->print("parsed ext adj ");
        debugPort->println(iTemp);

        if (initialize) {
          //create object and set itemp as init value
        } else {
          //set object to change value to itemp
        }
        break;
      case endOfTransmission:
        debugPort->print("end of transmission");

        if (thisRestarted) {
          thisRestarted = false;
        }
        if (initialize) {
          initialize = false;
        }
        break;
      default:
        debugPort->print("unknown id ");
        debugPort->print(index);
        debugPort->print(" value ");
        debugPort->println(port->parseFloat());
    }
  }
}

void IMMega::printErrors() {
  uint8_t count = errors.getCount();

  if (count) {
    for (int i = 0; i < count; i++) {
      IMError error = (IMError) errors.get(i);

      switch(error) {
        case OVERFLOW :
          debugPort->println(captions.OVERFLOW);
          break;
        case NO_HLVL :
          debugPort->println(captions.NO_HLVL);
          break;
        case NO_CONNECTION :
          debugPort->println(captions.NO_CONNECTION);
          break;
        case NO_SD_CARD :
          debugPort->println(captions.NO_SD_CARD);
          break;
        case NO_SD_SPACE :
          debugPort->println(captions.NO_SD_SPACE);
          break;
        case NO_OUT_MTR :
          debugPort->println(captions.NO_OUT_MTR);
          break;
        case NO_RET_MTR :
          debugPort->println(captions.NO_RET_MTR);
          break;
        case NO_COND_MTR :
          debugPort->println(captions.NO_COND_MTR);
          break;
        case NO_SW :
          debugPort->println(captions.NO_SW);
          break;
        case NO_ALC :
          debugPort->println(captions.NO_ALC);
          break;
        case NO_BAR :
          debugPort->println(captions.NO_BAR);
          break;
        case NO_RTC :
          debugPort->println(captions.NO_RTC);
          break;
        case NO_STEAM_TRM :
          debugPort->println(captions.NO_STEAM_TRM);
          break;
        case NO_PIPE_TRM :
          debugPort->println(captions.NO_PIPE_TRM);
          break;
        case NO_COND_TRM :
          debugPort->println(captions.NO_COND_TRM);
          break;
        case NO_ENV_TRM :
          debugPort->println(captions.NO_ENV_TRM);
          break;
        case NO_HEAT :
          debugPort->println(captions.NO_HEAT);
          break;
        case NANO_BLACKOUT :
          debugPort->println(captions.NANO_BLACKOUT);
          break;
        case MEGA_BLACKOUT :
          debugPort->println(captions.MEGA_BLACKOUT);
          break;
        case TRANSMISSION_CORRUPTED :
          debugPort->println(captions.TRANSMISSION_CORRUPTED);
          break;
      }
    }
  } else {
    debugPort->println(captions.NO_ERROR);
  }
}
