#include "IMMega.h"

IMMega::IMMega() : InfiniteMoonshine(MEGA_RST_PIN) {}

void IMMega::setMasterSPI() {
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);
}

bool IMMega::initUI() {
  bool result = tft.init();
  result &= ts.init();
  drawInitPane();
  return result;
}

bool IMMega::init() {
  bool result = true;

  //init timer?
  timer.start();
  //timer.setupTime();
  //setMasterSPI();
  //initWatchdog();
  //disableWatchdog();

  debugPort = &Serial;
  debugPort->begin(usbSpeed);

  hours.reserve(2);
  minutes.reserve(2);
  
  debugPort->print("initializing screen.. ");

  if (initUI()) {
    debugPort->println("done in "+String(timer.check())+" ms");
  } else {
    debugPort->println("failed");
    timer.check();
    result = false;
  }
  /* 
  debugPort->print("initializing log.. ");
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
    errors.add(IMError::NO_TRM);
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
  debugPort->print("initializing serial interface.. ");
  port = &Serial1;
  port->begin(serialSpeed);
  debugPort->println("done in "+String(timer.check())+" ms");
  
  debugPort->print("waiting for nano.. ");
  waitingTimer.start();

  while(!port->available()) {
    if (waitingTimer.getElapsedTime() > callsignTimeout) {
      errors.add(IMError::NO_CONNECTION);
      result = false;
      break;
    }
  }
  waitingTimer.stop();

  if (errors.contains(IMError::NO_CONNECTION)) {
    debugPort->println("timeout reached. "+String(timer.check())+" ms");
  } else {
    debugPort->println("connection established in "+String(timer.check())+" ms");
  }
  */
  debugPort->println("initialization done in "+String(timer.stop())+" ms");
  
  if (result) {
    debugPort->println("system is ready to use");
    drawFrontPane();
    drawBottomBar();
  } else {
    debugPort->println("system initialization failure");
    drawErrorsPane();
  }

  return result;
}

void IMMega::loop() {
  //restartWatchdog();
  
  if (movingMotors()) {
    return;
  }
  
  /*
  if (millis() - responseTime >= callsignTimeout) {
    restartOther();
    responseTime = millis();
  }
  */
  if (!errors.isEmpty()) {
    debugPort->print("errors:");

    for (int i = 0; i < errors.getCount(); i++) {
      debugPort->print(" ");
      debugPort->print(errors.get(i));
    }
    debugPort->println();

    if (!handleErrors()) {
      drawErrorsPane();
    }
  }
  
  if (host.collectValues(session.inHeadState())) {
    update();
    //updateNodes();
    host.prepareToCollect(session.inHeadState());
  }
  handleTouch();
  blink();
}

void IMMega::debug() {
  //hlvl.debug();
  //delay(2000);
}

void IMMega::update() {
  queue = "";
  /*
  //session changes -> processed in createSession() or pauseSession() -> use changed flag
  session.getName();
  session.getStartTime();
  session.getSrcType();
  session.getSrcVol();
  session.getState();//drawBottomBar()
  session.isActive();
  session.isPaused();
  */

  if (session.getSteamTemp() != host.getSteamTemp()) {
    if (activePane == DASH1_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(0, DASH_DATA_YLO1, DASH_SLOT_WIDTH, DASH_DATA_YHI1);
      tft.print(String(host.getSteamTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data11);
    }
    session.setSteamTemp(host.getSteamTemp());
    addToQueue(LogIndex::STEAM_TEMP, String(session.getSteamTemp()));
  }

  if (session.getPipeTemp() != host.getPipeTemp()) {
    if (activePane == DASH1_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(DASH_SLOT_WIDTH, DASH_DATA_YLO1, 2*DASH_SLOT_WIDTH, DASH_DATA_YHI1);
      tft.print(String(host.getPipeTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data12);
    }
    session.setPipeTemp(host.getPipeTemp());
    addToQueue(LogIndex::PIPE_TEMP, String(session.getPipeTemp()));
  }

  if (session.getAlcLvl() != host.getAlcLvl()) {
    if (activePane == DASH1_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(2*DASH_SLOT_WIDTH, DASH_DATA_YLO1, SCR_WIDTH, DASH_DATA_YHI1);
      tft.print(String(host.getAlcLvl()), DATA_FONT_SIZE, MAIN_COLOR, data13);
    }
    session.setAlcLvl(host.getAlcLvl());
    addToQueue(LogIndex::ALC_LEVEL, String(session.getAlcLvl()));
  }

  if (session.getCalcTemp() != host.getCalcTemp()) {
    if (activePane == DASH1_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(0, DASH_DATA_YLO2, DASH_SLOT_WIDTH, DASH_DATA_YHI2);
      tft.print(String(host.getCalcTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data21);
    }
    session.setCalcTemp(host.getCalcTemp());
  }

  if (session.getEnvTemp() != host.getEnvTemp()) {
    if (activePane == DASH1_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(DASH_SLOT_WIDTH, DASH_DATA_YLO2, 2*DASH_SLOT_WIDTH, DASH_DATA_YHI2);
      tft.print(String(host.getEnvTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data22);
    }
    session.setEnvTemp(host.getEnvTemp());
    addToQueue(LogIndex::ENV_TEMP, String(session.getEnvTemp()));
  }

  if ((int)session.getPressure() != (int)host.getPressure()) {
    if (activePane == DASH1_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(2*DASH_SLOT_WIDTH, DASH_DATA_YLO2, SCR_WIDTH, DASH_DATA_YHI2);
      tft.print(String((int)host.getPressure()), DATA_FONT_SIZE, MAIN_COLOR, data23);
    }
    session.setPressure(host.getPressure());
    addToQueue(LogIndex::PRESSURE, String(session.getPressure()));
  }
  
  if (session.getExtSpeed() != host.getExtSpeed()) {
    if (activePane == DASH2_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(0, DASH_DATA_YLO1, DASH_SLOT_WIDTH, DASH_DATA_YHI1);
      tft.print(String(host.getExtSpeed()), DATA_FONT_SIZE, MAIN_COLOR, data11);
    }
    session.setExtSpeed(host.getExtSpeed());
    addToQueue(LogIndex::EXT_SPEED, String(session.getExtSpeed()));
  }
  /*
  if (host.outMtrMoving()) {
    if (activePane == DASH2_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(topLabel11);
      tft.setColor(TARGET_COLOR);
      tft.setFontSize(LBL_FONT_SIZE);
      tft.print(String(captions.ARROW_RIGHT)+" "+String(host.getOutMtrPos()), topLabel11);
    }
  } else {
    if (activePane == DASH2_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(topLabel11);
    }
  }
  */
  if (session.getRefluxSpeed() != host.getRefluxSpeed()) {
    if (activePane == DASH2_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(DASH_SLOT_WIDTH, DASH_DATA_YLO1, 2*DASH_SLOT_WIDTH, DASH_DATA_YHI1);
      tft.print(String(host.getRefluxSpeed()), DATA_FONT_SIZE, MAIN_COLOR, data12);
    }
    session.setRefluxSpeed(host.getRefluxSpeed());
    addToQueue(LogIndex::REF_SPEED, String(session.getRefluxSpeed()));
  }
  /*
  if (host.retMtrMoving()) {
    if (activePane == DASH2_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(topLabel12);
      tft.setColor(TARGET_COLOR);
      tft.setFontSize(LBL_FONT_SIZE);
      tft.print(String(captions.ARROW_RIGHT)+" "+String(host.getRetMtrPos()), topLabel12);
    }
  } else {
    if (activePane == DASH2_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(topLabel12);
    }
  }
  */
  if (session.getWaterSpeed() != host.getWaterSpeed()) {
    if (activePane == DASH2_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(2*DASH_SLOT_WIDTH, DASH_DATA_YLO1, SCR_WIDTH, DASH_DATA_YHI1);
      tft.print(String(host.getWaterSpeed()), DATA_FONT_SIZE, MAIN_COLOR, data13);
    }
    session.setWaterSpeed(host.getWaterSpeed());
    addToQueue(LogIndex::WATER_SPEED, String(session.getWaterSpeed()));
  }
  /*
  if (host.condMtrMoving()) {
    if (activePane == DASH2_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(topLabel13);
      tft.setColor(TARGET_COLOR);
      tft.setFontSize(LBL_FONT_SIZE);
      tft.print(String(captions.ARROW_RIGHT)+" "+String(host.getCondMtrPos()), topLabel13);
    }
  } else {
    if (activePane == DASH2_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(topLabel13);
    }
  }
  */
  if (session.getHeatPwr() != host.getHeatPwr()) {
    if (activePane == DASH2_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(0, DASH_DATA_YLO2, DASH_SLOT_WIDTH, DASH_DATA_YHI2);
      tft.print(String(host.getHeatPwr()), DATA_FONT_SIZE, MAIN_COLOR, data21);
    }
    session.setHeatPwr(host.getHeatPwr());
    addToQueue(LogIndex::HEAT, String(session.getHeatPwr()));
  }

  if (session.getHydroLvl() != host.getHydroLvl()) {
    if (activePane == DASH2_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(DASH_SLOT_WIDTH, DASH_DATA_YLO2, 2*DASH_SLOT_WIDTH, DASH_DATA_YHI2);
      tft.setColor(MAIN_COLOR);
      tft.setFontSize(DATA_FONT_SIZE);

      switch (host.getHydroLvl()) {
        case OVR:
          tft.print(captions.OVR_LVL, data22);
          break;
        case HI:
          tft.print(captions.HI_LVL, data22);
          break;
        case OK:
          tft.print(captions.OK_LVL, data22);
          break;
        default:
          tft.print(captions.LO_LVL, data22);
          break;
      }
    }
    session.setHydroLvl(host.getHydroLvl());
    addToQueue(LogIndex::HYDRO_LEVEL, String(session.getHydroLvl()));
  }

  if (session.getCondTemp() != host.getCondTemp()) {
    if (activePane == DASH2_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(2*DASH_SLOT_WIDTH, DASH_DATA_YLO2, SCR_WIDTH, DASH_DATA_YHI2);
      tft.print(String(host.getCondTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data23);
    }
    session.setCondTemp(host.getCondTemp());
    addToQueue(LogIndex::COND_TEMP, String(session.getCondTemp()));
  }

  if (session.getExtAdj() != host.getExtAdj()) {
    if (activePane == DASH3_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(0, DASH_DATA_YLO1, DASH_SLOT_WIDTH, DASH_DATA_YHI1);
      tft.print(String(host.getExtAdj()), DATA_FONT_SIZE, MAIN_COLOR, data11);
    }
    session.setExtAdj(host.getExtAdj());
    addToQueue(LogIndex::EXT_ADJ, String(session.getExtAdj()));
  }

  if (session.getWaterAdj() != host.getWaterAdj()) {
    if (activePane == DASH3_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(DASH_SLOT_WIDTH, DASH_DATA_YLO1, 2*DASH_SLOT_WIDTH, DASH_DATA_YHI1);
      tft.print(String(host.getWaterAdj()), DATA_FONT_SIZE, MAIN_COLOR, data12);
    }
    session.setWaterAdj(host.getWaterAdj());
    addToQueue(LogIndex::WATER_ADJ, String(session.getWaterAdj()));
  }

  if (session.getHeatAdj() != host.getHeatAdj()) {
    if (activePane == DASH3_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(2*DASH_SLOT_WIDTH, DASH_DATA_YLO1, SCR_WIDTH, DASH_DATA_YHI1);
      tft.print(String(host.getHeatAdj()), DATA_FONT_SIZE, MAIN_COLOR, data13);
    }
    session.setHeatAdj(host.getHeatAdj());
    addToQueue(LogIndex::HEAT_ADJ, String(session.getHeatAdj()));
  }

  if (session.getSwitchPos() != host.getSwitchPos()) {
    if (activePane == DASH3_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(0, DASH_DATA_YLO2, DASH_SLOT_WIDTH, DASH_DATA_YHI2);

      if (host.getSwitchPos()) {
        tft.print(String(captions.BODY_POS), DATA_FONT_SIZE, MAIN_COLOR, data21);
      } else {
        tft.print(String(captions.HEAD_POS), DATA_FONT_SIZE, MAIN_COLOR, data21);
      }
      
    }
    session.setSwitchPos(host.getSwitchPos());
    addToQueue(LogIndex::SW, String(session.getSwitchPos()));
  }
  
  if (session.getRefluxRatio() != host.getRefluxRatio()) {
    if (activePane == DASH3_PANE) {
      tft.setColor(BACKGROUND_COLOR);
      tft.fillRect(DASH_SLOT_WIDTH, DASH_DATA_YLO2, 2*DASH_SLOT_WIDTH, DASH_DATA_YHI2);
      tft.print(String(host.getRefluxRatio()), DATA_FONT_SIZE, MAIN_COLOR, data22);
    }
    session.setRefluxRatio(host.getRefluxRatio());
    addToQueue(LogIndex::RF, String(session.getRefluxRatio()));
  }
  /*
  //calculate
  session.getHeadOutML();
  session.getBodyOutML();
  session.getUsedWaterL();
  session.getUsedPowerKW();
  session.getElapsedTime();
  */
  /*
  if (queue.length()) {
    endQueue();
  }
  */
  if (changed) {
    logData();
    changed = false;
  }
}

void IMMega::updateNodes() {
  if (MANUAL_MODE) {
    condNode.cool();
    return;
  }
  switch (session.getState()) {
    case STAND_BY_STATE :
      condNode.standBy();
      break;
    case HEAT_STATE :
      condNode.cool();
      break;
    case STAB_STATE :
      condNode.cool();
      break;
    case HEAD_STATE :
      condNode.cool();
      break;
    case PRE_BODY_STATE :
      condNode.cool();
      break;
    case BODY_STATE :
      condNode.cool();
      break;
    case PRE_TAIL_STATE :
      condNode.cool();
      break;
    case FINISH_STATE :
      condNode.standBy();
      break;
    case CANCEL_STATE :
      condNode.standBy();
      break;
    case ERROR_STATE :
      condNode.standBy();
      break;
  }
}

bool IMMega::movingMotors() {
  outMtr.loop();
  retMtr.loop();
  condMtr.loop();
  swMtr.loop();

  bool movement = host.outMtrMoving();
  movement |= host.retMtrMoving();
  movement |= host.condMtrMoving();
  movement |= host.swMtrMoving();

  return movement;
}

bool IMMega::handleErrors() {
  bool result = false;
  //todo reconnect sensors
  return result;
}

void IMMega::receiveCallsign() {
  char message = port->read();

  debugText = "\nincoming callsign: "+String(message);

  switch(message) {
    case initSign:
      if (callsign == onlineSign) {
        errors.add(IMError::NANO_BLACKOUT);
        debugText += "\nnano blackout. sending data:";
        sendData();
        responseTime = millis();
        logRestart();
      } else {
        readPrevLog();
        //if session incomplete (power failure) -> load from log 
        //as if restarted (mtr cur pos), sendData() and resume
        debugText += "\npower on. sending init data:";
        sendData();
        initialize = false;
        responseTime = millis();
      }
      break;
    case onlineSign:
      debugText += "\nsending response: "+String(callsign);
      sendCallsign();
      responseTime = millis();
      break;
    case restartSign:
      thisRestarted = true;
      debugText += "\nmega blackout. receiving data:";
      receiveData();
      responseTime = millis();
      logRestart();
      break;
    case dataSign:
      receiveData();
      responseTime = millis();
      break;
    default:
      errors.add(IMError::TRANSMISSION_CORRUPTED);
      debugText += "\nunknown callsign. transmission corrupted error.";
      //repeat transfer, attempts += 1; then if fails -> error
  }
  debugPort->println(debugText);
  //printDebugText();
}

void IMMega::sendData() {
  if (otherRestarted) {
    callsign = restartSign;
  } else {
    callsign = dataSign;
  }
  queue = String(callsign);

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
}

void IMMega::receiveData() {
  transfering = true;

  while (port->available()) {
    int index = port->parseInt();
    long iTemp;
    float fTemp;

    switch(index) {
      case LogIndex::SESSION_NAME :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (session name) "+String(iTemp);
        session.setName(iTemp);
        break;
      case LogIndex::START_TIME :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (start time) "+String(iTemp);
        session.setStartTime(iTemp);
        break;
      case LogIndex::UPD_TIME :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (upd time) "+String(iTemp);
        updTime = iTemp;
        break;
      case LogIndex::STATE :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (state) "+String(iTemp);
        session.setState(iTemp);
        break;
      case LogIndex::PAUSE :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (pause) "+String(iTemp);
        session.setManualPause(iTemp);
        break;
      case LogIndex::SRC_VOL :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (src vol) "+String(iTemp);
        session.setSrcVol(iTemp);
        break;
      case LogIndex::SRC_TYPE :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (src type) "+String(iTemp);
        session.setSrcType(iTemp);
        break;
      case LogIndex::ERROR_CODES :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (error) "+String(iTemp);
        errors.add(iTemp);
        break;
      case LogIndex::WATER_SPEED :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (water speed) "+String(iTemp);
        session.setWaterSpeed(iTemp);
        host.restoreWaterSpeed(iTemp);
        break;
      case LogIndex::WATER_ADJ :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (water adj) "+String(iTemp);
        session.setWaterAdj(iTemp);
        host.setWaterAdj(iTemp);
        break;
      case LogIndex::SW :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (switch pos) "+String(iTemp);
        session.setSwitchPos(iTemp);
        host.restoreSwitch(iTemp);
        break;
      case LogIndex::HEAT :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (heat pwr) "+String(iTemp);
        session.setHeatPwr(iTemp);
        host.setHeatPwr(iTemp);
        break;
      case LogIndex::HEAT_ADJ :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (heat adj) "+String(iTemp);
        session.setHeatAdj(iTemp);
        host.setHeatAdj(iTemp);
        break;
      case LogIndex::RF :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (reflux ratio) "+String(iTemp);
        session.setRefluxRatio(iTemp);
        host.setRefluxRatio(iTemp);
        break;
      case LogIndex::EXT_SPEED :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (ext speed) "+String(iTemp);
        session.setExtSpeed(iTemp);
        host.restoreExtSpeed(iTemp);
        break;
      case LogIndex::REF_SPEED :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (reflux speed) "+String(iTemp);
        session.setRefluxSpeed(iTemp);
        host.restoreRefluxSpeed(iTemp);
        break;
      case LogIndex::EXT_ADJ :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (ext adj) "+String(iTemp);
        session.setExtAdj(iTemp);
        host.setExtAdj(iTemp);
        break;
      case LogIndex::HEAD_OUT_ML :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (head out) "+String(iTemp);
        session.setHeadOutML(iTemp);//add calculated quantity for freezing time
        break;
      case LogIndex::BODY_OUT_ML :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (body out) "+String(iTemp);
        session.setBodyOutML(iTemp);//add calculated quantity for freezing time
        break;
      case LogIndex::USED_WATER_L :
        fTemp = port->parseFloat();
        debugText += "\n"+String(index)+" (used water l) "+String(fTemp);
        session.setUsedWaterL(fTemp);//add calculated quantity for freezing time
        break;
      case LogIndex::USED_POWER_KW :
        fTemp = port->parseFloat();
        debugText += "\n"+String(index)+" (used power kW) "+String(fTemp);
        session.setUsedPowerKW(fTemp);//add calculated quantity for freezing time
        break;
      case endOfTransmission:
        debugText += "\n"+String(index)+" (eot)";
        transfering = false;
        if (initialize) {
          initialize = false;
          debugText += "\ninit done.";
        }
        if (errors.contains(IMError::TRANSMISSION_CORRUPTED)) {
          errors.remove(IMError::TRANSMISSION_CORRUPTED);
        }
        break;
      default:
       debugText += "\n"+String(index)+" (unknown) "+String(port->parseInt());
    }
  }
  if (transfering) {
    errors.add(IMError::TRANSMISSION_CORRUPTED);
    debugText += "\ntransfer incomplete.";
    transfering = false;
  }
}

void IMMega::applyEditing() {
  if (KEY_DIGIT_LIMIT > INT16_MAX) {
    if (editValue > INT16_MAX) {
      editValue = INT16_MAX;
    }
  }
  if (editLabel == captions.OUT_MTR_LBL) {
    host.setExtSpeed(editValue);
    
    if (host.getRefluxRatio()) {
      host.setRefluxSpeed(editValue * host.getRefluxRatio());
    }
  }
  if (editLabel == captions.RET_MTR_LBL) {
    host.setRefluxSpeed(editValue);
  }
  if (editLabel == captions.COND_MTR_LBL) {
    host.setWaterSpeed(editValue);
  }
  if (editLabel == captions.HEAT_PWR_LBL) {
    if (editValue > UINT8_MAX) {
      editValue = UINT8_MAX;
    }
    host.setHeatPwr(editValue);
  }
  if (editLabel == captions.EXT_ADJ_LBL) {
    host.setExtAdj(editValue);
  }
  if (editLabel == captions.COND_ADJ_LBL) {
    host.setWaterAdj(editValue);
  }
  if (editLabel == captions.HEAT_ADJ_LBL) {
    if (editValue > UINT8_MAX) {
      editValue = UINT8_MAX;
    }
    host.setHeatAdj(editValue);
  }
  if (editLabel == captions.SW_LBL) {
    if (editValue) {
      editValue = 1;
    }
    host.setSwitchPos(editValue);
  }
  if (editLabel == captions.RF_LBL) {
    if (editValue > UINT8_MAX) {
      editValue = UINT8_MAX;
    }
    host.setRefluxRatio(editValue);
  }
}

void IMMega::handleTouch() {
  IMPoint touch = ts.getTouchPosition();

  if (touch.hasValue()) {
    /*
    if (MANUAL_MODE && sessionIsActive()) {
      if (bottomLeftRect.hasPoint(touch)) {
        switch(currentState) {
          case STAB_STATE:
            setState(HEAT_STATE);
            break;
          case HEAD_STATE:
            setState(STAB_STATE);
            break;
          case PRE_BODY_STATE:
            setState(HEAD_STATE);
            break;
          case BODY_STATE:
            setState(PRE_BODY_STATE);
            break;
          case PRE_TAIL_STATE:
            setState(BODY_STATE);
            break;
        }
      }
      if (bottomRightRect.hasPoint(touch)) {
        switch(currentState) {
          case HEAT_STATE:
            setState(STAB_STATE);
            break;
          case STAB_STATE:
            setState(HEAD_STATE);
            break;
          case HEAD_STATE:
            setState(PRE_BODY_STATE);
            break;
          case PRE_BODY_STATE:
            setState(BODY_STATE);
            break;
          case BODY_STATE:
            setState(PRE_TAIL_STATE);
            break;
          case PRE_TAIL_STATE:
            setState(FINISH_STATE);
            break;
        }
      }
    }
    */
    switch(activePane) {
      case FRONT_PANE:
        if (topLeftRect.hasPoint(touch)) {
          if (session.isActive()) {
            //abort session -> confirm dialog
          } else {
            //start session
          }
        }
        if (topL2Rect.hasPoint(touch) && MANUAL_MODE) {
          //pause session
        }
        if (topRightRect.hasPoint(touch)) {
          drawDash1();
        }
        if (bottomBar.hasPoint(touch) && session.getState() == STAND_BY_STATE) {
          //start session
        }
        break;
      case DASH1_PANE:
        if (topLeftRect.hasPoint(touch)) {
          drawFrontPane();
        }
        if (topRightRect.hasPoint(touch)) {
          drawDash2();
        }
        break;
      case DASH2_PANE:
        if (topLeftRect.hasPoint(touch)) {
          drawDash1();
        }
        if (topRightRect.hasPoint(touch)) {
          drawDash3();
        }
        if (MANUAL_MODE) {
          if (slot11.hasPoint(touch)) {
            drawKeyboard(host.getExtSpeed(), captions.OUT_MTR_LBL);
          }
          if (slot12.hasPoint(touch)) {
            drawKeyboard(host.getRefluxSpeed(), captions.RET_MTR_LBL);
          }
          if (slot13.hasPoint(touch)) {
            drawKeyboard(host.getWaterSpeed(), captions.COND_MTR_LBL);
          }
          if (slot21.hasPoint(touch)) {
            drawKeyboard(host.getHeatPwr(), captions.HEAT_PWR_LBL);
          }
        }
        break;
      case DASH3_PANE:
        if (topLeftRect.hasPoint(touch)) {
          drawDash2();
        }
        if (MANUAL_MODE) {
          if (slot11.hasPoint(touch)) {
            drawKeyboard(host.getExtAdj(), captions.EXT_ADJ_LBL);
          }
          if (slot12.hasPoint(touch)) {
            drawKeyboard(host.getWaterAdj(), captions.COND_ADJ_LBL);
          }
          if (slot13.hasPoint(touch)) {
            drawKeyboard(host.getHeatAdj(), captions.HEAT_ADJ_LBL);
          }
          if (slot21.hasPoint(touch)) {
            drawKeyboard(host.getSwitchPos(), captions.SW_LBL);
          }
          if (slot22.hasPoint(touch)) {
            drawKeyboard(host.getRefluxRatio(), captions.RF_LBL);
          }
        }
        break;
      case ERROR_PANE:
        break;
      case KEYBOARD:
      appendAllowed = !(editValue / KEY_DIGIT_LIMIT);

        if (key1.hasPoint(touch) && appendAllowed) {
          editValue *= 10;
          editValue += 1;
          drawKeyboardData();
        }
        if (key2.hasPoint(touch) && appendAllowed) {
          editValue *= 10;
          editValue += 2;
          drawKeyboardData();
        }
        if (key3.hasPoint(touch) && appendAllowed) {
          editValue *= 10;
          editValue += 3;
          drawKeyboardData();
        }
        if (key4.hasPoint(touch) && appendAllowed) {
          editValue *= 10;
          editValue += 4;
          drawKeyboardData();
        }
        if (key5.hasPoint(touch) && appendAllowed) {
          editValue *= 10;
          editValue += 5;
          drawKeyboardData();
        }
        if (key6.hasPoint(touch) && appendAllowed) {
          editValue *= 10;
          editValue += 6;
          drawKeyboardData();
        }
        if (key7.hasPoint(touch) && appendAllowed) {
          editValue *= 10;
          editValue += 7;
          drawKeyboardData();
        }
        if (key8.hasPoint(touch) && appendAllowed) {
          editValue *= 10;
          editValue += 8;
          drawKeyboardData();
        }
        if (key9.hasPoint(touch) && appendAllowed) {
          editValue *= 10;
          editValue += 9;
          drawKeyboardData();
        }
        if (key0.hasPoint(touch) && appendAllowed) {
          editValue *= 10;
          drawKeyboardData();
        }
        if (keyPlus.hasPoint(touch)) {
          if (editValue < KEY_DIGIT_LIMIT) {
            editValue += 1;
            drawKeyboardData();
          }
        }
        if (keyMinus.hasPoint(touch)) {
          if (editValue > 0) {
            editValue -= 1;
            drawKeyboardData();
          }
        }
        if (keyBackspace.hasPoint(touch)) {
          editValue /= 10;
          drawKeyboardData();
        }
        if (keyClear.hasPoint(touch)) {
          editValue = 0;
          drawKeyboardData();
        }
        if (keyCancel.hasPoint(touch)) {
          drawPrevPane();
        }
        if (keyOK.hasPoint(touch)) {
          applyEditing();
          drawPrevPane();
        }
        break;
    }
  }
}

void IMMega::drawBottomBar() {
  tft.setColor(BACKGROUND_COLOR);
  tft.fillRect(bottomBar);
  tft.setColor(MAIN_COLOR);
  tft.setFontSize(HDR_FONT_SIZE);
  tft.drawLine(0, BAR_HEIGHT, SCR_WIDTH, BAR_HEIGHT);
  /*
  if (MANUAL_MODE && sessionIsActive()) {
    if ((int8_t)currentState > 1) {
      tft.print(captions.ARROW_LEFT, bottomLeftRect);
    }
    tft.print(captions.ARROW_RIGHT, bottomRightRect);
  }
  */
  if (MANUAL_MODE) {
    tft.print(String(captions.MANUAL_MODE_LBL), bottomBar);
  } else {
    tft.print(String(captions.getStateString(session.getState())), bottomBar);
  }
}

void IMMega::drawPrevPane() {
  bool drawBottom = activePane == KEYBOARD;

  switch(prevActivePane) {
    case FRONT_PANE:
      drawFrontPane();
      break;
    case DASH1_PANE:
      drawDash1();
      break;
    case DASH2_PANE:
      drawDash2();
      break;
    case DASH3_PANE:
      drawDash3();
      break;
  }
  if (drawBottom) {
    drawBottomBar();
  }
}

void IMMega::drawInitPane() {
  tft.paintBackground();
  tft.print(captions.STARTING, PLAIN_FONT_SIZE, MAIN_COLOR, fullScr);

  activePane = Panes::INIT_PANE;
  prevActivePane = activePane;
}

void IMMega::drawFrontPane() {
  tft.clearPane();
  tft.setColor(MAIN_COLOR);
  tft.setFontSize(HDR_FONT_SIZE);
  tft.drawLine(0, TOP_BAR_HEIGHT, SCR_WIDTH, TOP_BAR_HEIGHT);

  if (!MANUAL_MODE) {
  if (session.isActive()) {
    tft.print(captions.ABORT_SESSION, topLeftRect);
    if (MANUAL_MODE) {
      tft.print(captions.PAUSE_SESSION, topL2Rect);
    }
    //print session parameters in scrBar
  } else {
    tft.print(captions.NEW_SESSION, topLeftRect);
    //clear session parameters
  }
  }
  tft.print(captions.INFO, topRightRect);
  drawHH();
  drawMM();

  prevActivePane = activePane;
  activePane = Panes::FRONT_PANE;
}

void IMMega::printDebugText() {
  tft.paintBackground();
  tft.print(debugText, ERR_FONT_SIZE, TEXT_COLOR, 0, SCR_HEIGHT);
}

void IMMega::drawMM() {
  mm = timer.getMM();
  minutes = String(mm/10) + String(mm%10);
  tft.setColor(BACKGROUND_COLOR);
  tft.fillRect(minutesRect);
  tft.printNum(minutes, minutesRect);
}

void IMMega::drawHH() {
  hh = timer.getHH();
  hours = String(hh/10) + String(hh%10);
  tft.setColor(BACKGROUND_COLOR);
  tft.fillRect(hoursRect);
  tft.printNum(hours, hoursRect);
}

void IMMega::blink() {
  if (activePane != FRONT_PANE) {
    return;
  }
  if (millis() - lastBlinkTime < blinkTimeout) {
    return;
  }
  if (hh != timer.getHH()) {
    drawHH();
  }
  if (mm != timer.getMM()) {
    drawMM();
  }
  if (blinkVisible) {
    tft.printNum(captions.TWO_SPOT, twospotRect);
  } else {
    tft.setColor(BACKGROUND_COLOR);
    tft.fillRect(twospotRect);
  }
  blinkVisible = !blinkVisible;
  lastBlinkTime = millis();
}

void IMMega::printErrors() {
  if (errCount) {
    errText = "";

    for (int i = 0; i < errCount; i++) {
      IMError error = (IMError) displayedErrors.get(i);

      switch(error) {
        case OVERFLOW :
          errText += String(captions.OVERFLOW) + "\n";
          break;
        case NO_HLVL :
          errText += String(captions.NO_HLVL) + "\n";
          break;
        case NO_CONNECTION :
          errText += String(captions.NO_CONNECTION) + "\n";
          break;
        case NO_SD_CARD :
          errText += String(captions.NO_SD_CARD) + "\n";
          break;
        case NO_SD_SPACE :
          errText += String(captions.NO_SD_SPACE) + "\n";
          break;
        case NO_OUT_MTR :
          errText += String(captions.NO_OUT_MTR) + "\n";
          break;
        case NO_RET_MTR :
          errText += String(captions.NO_RET_MTR) + "\n";
          break;
        case NO_COND_MTR :
          errText += String(captions.NO_COND_MTR) + "\n";
          break;
        case NO_SW :
          errText += String(captions.NO_SW) + "\n";
          break;
        case NO_ALC :
          errText += String(captions.NO_ALC) + "\n";
          break;
        case NO_BAR :
          errText += String(captions.NO_BAR) + "\n";
          break;
        case NO_RTC :
          errText += String(captions.NO_RTC) + "\n";
          break;
        case NO_STEAM_TRM :
          errText += String(captions.NO_STEAM_TRM) + "\n";
          break;
        case NO_PIPE_TRM :
          errText += String(captions.NO_PIPE_TRM) + "\n";
          break;
        case NO_COND_TRM :
          errText += String(captions.NO_COND_TRM) + "\n";
          break;
        case NO_ENV_TRM :
          errText += String(captions.NO_ENV_TRM) + "\n";
          break;
        case NO_HEAT :
          errText += String(captions.NO_HEAT) + "\n";
          break;
        case NANO_BLACKOUT :
          errText += String(captions.NANO_BLACKOUT) + "\n";
          break;
        case MEGA_BLACKOUT :
          errText += String(captions.MEGA_BLACKOUT) + "\n";
          break;
        case TRANSMISSION_CORRUPTED :
          errText += String(captions.TRANSMISSION_CORRUPTED) + "\n";
          break;
        case NO_LOG_DIR :
          errText += String(captions.NO_LOG_DIR) + "\n";
          break;
      }
    }
  } else {
    errText = String(captions.NO_ERROR);
  }
  tft.setColor(BACKGROUND_COLOR);
  tft.fillRect(0, BAR_HEIGHT, SCR_WIDTH, TOP_BAR_HEIGHT-1);
  tft.print(errText, ERR_FONT_SIZE, TEXT_COLOR, 0, TOP_BAR_HEIGHT-1);
}

void IMMega::drawErrorsPane() {
  errCount = errors.getCount();

  if (activePane == ERROR_PANE) {
    bool changed = false;

    if (errCount != displayedErrors.getCount()) {
      changed = true;
    } else {
      for (int i = 0; i < errCount; i++) {
        if (!displayedErrors.contains(errors.get(i))) {
          displayedErrors.add(errors.get(i));
          changed = true;
        }
      }
    }
    if (changed) {
      printErrors();
    }
  } else {
    displayedErrors.clear();

    for (int i = 0; i < errCount; i++) {
      displayedErrors.add((IMError)errors.get(i));
    }
    tft.clearPane();
    tft.setColor(ERROR_COLOR);
    tft.setFontSize(HDR_FONT_SIZE);
    tft.drawLine(0, TOP_BAR_HEIGHT, SCR_WIDTH, TOP_BAR_HEIGHT);
    tft.print(captions.ERRORS, topBar);
    printErrors();

    prevActivePane = activePane;
    activePane = Panes::ERROR_PANE;
  }
}

void IMMega::drawDash1Data() {
  tft.setFontSize(DATA_FONT_SIZE);
  tft.setColor(MAIN_COLOR);
  tft.print(String(host.getSteamTemp(), DATA_PRECISION), data11);
  tft.print(String(host.getPipeTemp(), DATA_PRECISION), data12);
  tft.print(String(host.getAlcLvl()), data13);
  tft.print(String(host.getCalcTemp(), DATA_PRECISION), data21);
  tft.print(String(host.getEnvTemp(), DATA_PRECISION), data22);
  tft.print(String((int)host.getPressure()), data23);

  tft.setFontSize(LBL_FONT_SIZE);
  tft.setColor(MAIN_COLOR_FLAT);
  tft.print(captions.STEAM_TEMP_LBL, label11);
  tft.print(captions.PIPE_TEMP_LBL, label12);
  tft.print(captions.ALC_LVL_LBL, label13);
  tft.print(captions.CALC_TEMP_LBL, label21);
  tft.print(captions.ENV_TEMP_LBL, label22);
  tft.print(captions.PRES_LBL, label23);
}

void IMMega::drawDash1() {
  tft.clearPane();
  tft.setColor(MAIN_COLOR);
  tft.setFontSize(HDR_FONT_SIZE);
  tft.drawLine(0, TOP_BAR_HEIGHT, SCR_WIDTH, TOP_BAR_HEIGHT);

  tft.print(captions.DASH1_HDR, topBar);
  tft.print(captions.ARROW_LEFT, topLeftRect);
  tft.print(captions.ARROW_RIGHT, topRightRect);

  drawDash1Data();
  
  prevActivePane = activePane;
  activePane = Panes::DASH1_PANE;
}

void IMMega::drawDash2Data() {
  tft.setColor(MAIN_COLOR);
  tft.setFontSize(DATA_FONT_SIZE);

  tft.print(String(host.getExtSpeed()), data11);
  tft.print(String(host.getRefluxSpeed()), data12);
  tft.print(String(host.getWaterSpeed()), data13);
  tft.print(String(host.getHeatPwr()), data21);

  switch (host.getHydroLvl()) {
    case OVR:
      tft.print(captions.OVR_LVL, data22);
      break;
    case HI:
      tft.print(captions.HI_LVL, data22);
      break;
    case OK:
      tft.print(captions.OK_LVL, data22);
      break;
    default:
      tft.print(captions.LO_LVL, data22);
      break;
  }
  tft.print(String(host.getCondTemp(), DATA_PRECISION), data23);

  tft.setColor(MAIN_COLOR_FLAT);
  tft.setFontSize(LBL_FONT_SIZE);
  tft.print(captions.OUT_MTR_LBL, label11);
  tft.print(captions.RET_MTR_LBL, label12);
  tft.print(captions.COND_MTR_LBL, label13);
  tft.print(captions.HEAT_PWR_LBL, label21);
  tft.print(captions.HLVL_LBL, label22);
  tft.print(captions.COND_TEMP_LBL, label23);
}

void IMMega::drawDash2() {
  tft.clearPane();
  tft.setColor(MAIN_COLOR);
  tft.setFontSize(HDR_FONT_SIZE);
  tft.drawLine(0, TOP_BAR_HEIGHT, SCR_WIDTH, TOP_BAR_HEIGHT);

  tft.print(captions.DASH2_HDR, topBar);
  tft.print(captions.ARROW_LEFT, topLeftRect);
  tft.print(captions.ARROW_RIGHT, topRightRect);

  drawDash2Data();
  
  prevActivePane = activePane;
  activePane = Panes::DASH2_PANE;
}

void IMMega::drawDash3Data() {
  tft.setColor(MAIN_COLOR);
  tft.setFontSize(DATA_FONT_SIZE);
  tft.print(String(host.getExtAdj()), data11);
  tft.print(String(host.getWaterAdj()), data12);
  tft.print(String(host.getHeatAdj()), data13);

  if (host.getSwitchPos()) {
    tft.print(captions.BODY_POS, data21);
  } else {
    tft.print(captions.HEAD_POS, data21);
  }
  tft.print(String(host.getRefluxRatio()), data22);

  tft.setColor(MAIN_COLOR_FLAT);
  tft.setFontSize(LBL_FONT_SIZE);
  tft.print(captions.EXT_ADJ_LBL, label11);
  tft.print(captions.COND_ADJ_LBL, label12);
  tft.print(captions.HEAT_ADJ_LBL, label13);
  tft.print(captions.SW_LBL, label21);
  tft.print(captions.RF_LBL, label22);
}

void IMMega::drawDash3() {
  tft.clearPane();
  tft.setColor(MAIN_COLOR);
  tft.setFontSize(HDR_FONT_SIZE);
  tft.drawLine(0, TOP_BAR_HEIGHT, SCR_WIDTH, TOP_BAR_HEIGHT);

  tft.print(captions.DASH3_HDR, topBar);
  tft.print(captions.ARROW_LEFT, topLeftRect);

  drawDash3Data();
  
  prevActivePane = activePane;
  activePane = Panes::DASH3_PANE;
}

void IMMega::drawKeyboardData() {
  tft.setColor(BACKGROUND_COLOR);
  tft.fillRect(keyData);
  tft.print(String(editValue), DATA_FONT_SIZE, MAIN_COLOR, keyDisplay);
}

void IMMega::drawKeyboard(int num, String label) {
  tft.paintBackground();
  tft.setColor(MAIN_COLOR);
  tft.setFontSize(DATA_FONT_SIZE);

  tft.drawLine(0, KEY_HEIGHT, SCR_WIDTH, KEY_HEIGHT);
  tft.drawLine(0, 2*KEY_HEIGHT, SCR_WIDTH, 2*KEY_HEIGHT);
  tft.drawLine(2*KEY_WIDTH, 3*KEY_HEIGHT, SCR_WIDTH, 3*KEY_HEIGHT);
  tft.drawLine(KEY_WIDTH, 0, KEY_WIDTH, 2*KEY_HEIGHT);
  tft.drawLine(2*KEY_WIDTH, 0, 2*KEY_WIDTH, SCR_HEIGHT);
  tft.drawLine(3*KEY_WIDTH, 0, 3*KEY_WIDTH, SCR_HEIGHT);
  tft.drawLine(4*KEY_WIDTH, 0, 4*KEY_WIDTH, SCR_HEIGHT);

  tft.print("1", key1);
  tft.print("2", key2);
  tft.print("3", key3);
  tft.print("4", key4);
  tft.print("5", key5);
  tft.print("6", key6);
  tft.print("7", key7);
  tft.print("8", key8);
  tft.print("9", key9);
  tft.print("0", key0);
  tft.print("+1", keyPlus);
  tft.print("-1", keyMinus);
  tft.print("<", keyBackspace);
  tft.print(captions.NO_KEY, keyCancel);
  tft.print(captions.CLR_KEY, keyClear);
  tft.print(captions.YES_KEY, keyOK);
  editLabel = label;
  tft.print(editLabel, LBL_FONT_SIZE, MAIN_COLOR_FLAT, keyLabel);
  editValue = num;
  drawKeyboardData();

  prevActivePane = activePane;
  activePane = Panes::KEYBOARD;
}

void IMMega::readPrevLog() {
  //find last log, read end. if @ finished -> stby
  //                         if not -> load checkpoint and resumePrevSession = true;
  //calculate timeout and water usage during blackout
  //if log ended with error -> check if it still present
  //if no log found -> stby
  //fills queue with commands
}

void IMMega::logRestart() {
  if (thisRestarted) {
    logRestart(Board::NANO);
    debugPort->println("nano restarted");
    thisRestarted = false;
  }
  if (otherRestarted) {
    logRestart(Board::MEGA);
    debugPort->println("mega restarted");
    otherRestarted = false;
  }
}

void IMMega::logRestart(Board board) {
  String rec = String(restartSign);

  rec += " ";
  rec += timer.getLogStamp();
  rec += " ";
  rec += String(board);

  //logger.println(rec);
}

void IMMega::logData() {
  //no log when paused
}
