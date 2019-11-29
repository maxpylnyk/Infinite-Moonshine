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

  timer.start();
  //timer.setupTime();
  initWatchdog();
  //setMasterSPI();

  if (DEBUG_MODE) {
    debugPort = &Serial;
    debugPort->begin(usbSpeed);
  }
  
  debugPort->print("initializing screen.. ");

  if (initUI()) {
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
    drawFrontPane();
  } else {
    debugPort->println("system initialization failure");
    showErrors();
  }

  return result;
}

void IMMega::loop() {
  restartWatchdog();
  //moveMotors();

  if (!errors.isEmpty()) {
    if (!handleErrors()) {
      showErrors();
    }
  }

  
  if (host.collectValues()) {
    //send to logic
    //sendData();
    //logData();
    requireRefresh();
    host.prepareToCollect();//place after refresh
  }
  //blink();
  handleTouch();
  refresh();
}

void IMMega::debug() {
  //hlvl.debug();
  //delay(2000);
}

bool IMMega::sessionIsActive() {
  return (int8_t)currentState > 0;
}

bool IMMega::setState(State newState) {
  currentState = newState;
  //apply changes
  return true;
}

void IMMega::moveMotors() {
  outMtr.loop();
  retMtr.loop();
  condMtr.loop();
  swMtr.loop();
}

bool IMMega::handleErrors() {
  bool result = true;
  //todo
  return result;
}

void IMMega::showErrors() {
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

  drawErrorsPane();
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
      case LogIndex::ENV_TEMP ://remove
        fTemp = port->parseFloat();
        debugPort->print("parsed env temp ");
        debugPort->println(fTemp);
        break;
      case LogIndex::PRESSURE ://remove
        fTemp = port->parseFloat();
        debugPort->print("parsed pressure ");
        debugPort->println(fTemp);
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

void IMMega::handleTouch() {
  IMPoint touch = ts.getTouchPosition();

  if (touch.hasValue()) {
    //Serial.println(String(touch.x)+" "+String(touch.y));
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
          if (sessionIsActive()) {
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
          //allow edit first 4 values
        }
        break;
      case DASH3_PANE:
        if (topLeftRect.hasPoint(touch)) {
          drawDash2();
        }
        if (MANUAL_MODE) {
          //allow edit all 5 values
        }
        break;
      case ERROR_PANE:
        drawFrontPane();
        break;
      case KEYBOARD:
        
        break;
    }
    prevActivePane = activePane;
  }
}

void IMMega::drawBottomBar() {
  /*
  if (MANUAL_MODE && sessionIsActive()) {
    if ((int8_t)currentState > 1) {
      tft.print(captions.ARROW_LEFT, HDR_FONT_SIZE, BACKGROUND_COLOR, bottomLeftRect);
    }
    tft.print(captions.ARROW_RIGHT, HDR_FONT_SIZE, BACKGROUND_COLOR, bottomRightRect);
  }
  */

  tft.print(String(captions.getStateString(currentState)), HDR_FONT_SIZE, BACKGROUND_COLOR, bottomBar);
}

void IMMega::drawInitPane() {
  tft.paintBackground();
  tft.print(captions.STARTING, PLAIN_FONT_SIZE, MAIN_COLOR, fullScr);

  activePane = Panes::INIT_PANE;
  prevActivePane = activePane;
  refreshTimeout = 0;

  refreshTime = millis();
  refreshRequired = false;
}

void IMMega::drawFrontPane() {
  tft.paintBackground();
  tft.setColor(MAIN_COLOR);
  tft.fillRect(topBar);
  tft.fillRect(bottomBar);

  if (sessionIsActive()) {
    tft.print(captions.ABORT_SESSION, HDR_FONT_SIZE, BACKGROUND_COLOR, topLeftRect);
    if (MANUAL_MODE) {
      tft.print(captions.PAUSE_SESSION, HDR_FONT_SIZE, BACKGROUND_COLOR, topL2Rect);
    }
  } else {
    tft.print(captions.NEW_SESSION, HDR_FONT_SIZE, BACKGROUND_COLOR, topLeftRect);
  }
  tft.print(captions.INFO, HDR_FONT_SIZE, BACKGROUND_COLOR, topRightRect);

  tft.printNum(timer.getTime(), timeRect);
  tft.print("Тип сырья объём", 2, MAIN_COLOR, srcBar);
  drawBottomBar();

  prevActivePane = activePane;
  activePane = Panes::FRONT_PANE;
  refreshTimeout = FRONT_PANE_TIMEOUT;

  refreshTime = millis();
  refreshRequired = false;
}

void IMMega::drawErrorsPane() {
  uint8_t count = errors.getCount();
  uint8_t offset = WIDTH_MULT * ERR_FONT_SIZE / 2;
  int x0 = 0;
  int y0 = SCR_HEIGHT - BAR_HEIGHT;
  IMRect header = IMRect(x0, y0, SCR_WIDTH, SCR_HEIGHT);
  tft.paintBackground();
  tft.setColor(ERROR_COLOR);
  tft.fillRect(header);
  tft.fillRect(bottomBar);
  tft.print(captions.ERRORS, HDR_FONT_SIZE, BACKGROUND_COLOR, header);
  drawBottomBar();
  x0 += offset;

  if (count) {
    for (int i = 0; i < count; i++) {
      IMError error = (IMError) errors.get(i);
      y0 += HEIGHT_MULT * ERR_FONT_SIZE + offset;

      switch(error) {
        case OVERFLOW :
          tft.print(captions.OVERFLOW, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_HLVL :
          tft.print(captions.NO_HLVL, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_CONNECTION :
          tft.print(captions.NO_CONNECTION, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_SD_CARD :
          tft.print(captions.NO_SD_CARD, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_SD_SPACE :
          tft.print(captions.NO_SD_SPACE, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_OUT_MTR :
          tft.print(captions.NO_OUT_MTR, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_RET_MTR :
          tft.print(captions.NO_RET_MTR, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_COND_MTR :
          tft.print(captions.NO_COND_MTR, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_SW :
          tft.print(captions.NO_SW, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_ALC :
          tft.print(captions.NO_ALC, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_BAR :
          tft.print(captions.NO_BAR, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_RTC :
          tft.print(captions.NO_RTC, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_STEAM_TRM :
          tft.print(captions.NO_STEAM_TRM, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_PIPE_TRM :
          tft.print(captions.NO_PIPE_TRM, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_COND_TRM :
          tft.print(captions.NO_COND_TRM, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_ENV_TRM :
          tft.print(captions.NO_ENV_TRM, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NO_HEAT :
          tft.print(captions.NO_HEAT, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case NANO_BLACKOUT :
          tft.print(captions.NANO_BLACKOUT, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case MEGA_BLACKOUT :
          tft.print(captions.MEGA_BLACKOUT, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
        case TRANSMISSION_CORRUPTED :
          tft.print(captions.TRANSMISSION_CORRUPTED, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
          break;
      }
    }
  } else {
    tft.print(captions.NO_ERROR, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
  }
  prevActivePane = activePane;
  activePane = Panes::ERROR_PANE;
  refreshTimeout = 0;

  refreshTime = millis();
  refreshRequired = false;
}

void IMMega::drawDash1Data() {
  tft.setColor(BACKGROUND_COLOR);
  tft.fillRect(IMRect(0, BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT-BAR_HEIGHT));

  tft.print(String(host.getSteamTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data11);
  tft.print(String(host.getPipeTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data12);
  tft.print(String(host.getAlcLvl()), DATA_FONT_SIZE, MAIN_COLOR, data13);
  tft.print(String(host.getCalcTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data21);
  tft.print(String(host.getEnvTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data22);
  tft.print(String((int)host.getPressure()), DATA_FONT_SIZE, MAIN_COLOR, data23);

  tft.print(captions.STEAM_TEMP_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label11);
  tft.print(captions.PIPE_TEMP_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label12);
  tft.print(captions.ALC_LVL_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label13);
  tft.print(captions.CALC_TEMP_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label21);
  tft.print(captions.ENV_TEMP_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label22);
  tft.print(captions.PRES_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label23);
}

void IMMega::drawDash1() {
  tft.paintBackground();
  tft.setColor(MAIN_COLOR);
  tft.fillRect(topBar);
  tft.fillRect(bottomBar);

  tft.print(captions.DASH1_HDR, HDR_FONT_SIZE, BACKGROUND_COLOR, topBar);
  tft.print(captions.ARROW_LEFT, HDR_FONT_SIZE, BACKGROUND_COLOR, topLeftRect);
  tft.print(captions.ARROW_RIGHT, HDR_FONT_SIZE, BACKGROUND_COLOR, topRightRect);

  drawDash1Data();
  drawBottomBar();
  
  prevActivePane = activePane;
  activePane = Panes::DASH1_PANE;
  refreshTimeout = DASHBOARD_TIMEOUT;

  refreshTime = millis();
  refreshRequired = false;
}

void IMMega::drawDash2Data() {
  tft.setColor(BACKGROUND_COLOR);
  tft.fillRect(IMRect(0, BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT-BAR_HEIGHT));

  tft.print(String(host.getOutMtrPos()), DATA_FONT_SIZE, MAIN_COLOR, data11);
  tft.print(String(host.getRetMtrPos()), DATA_FONT_SIZE, MAIN_COLOR, data12);
  tft.print(String(host.getCondMtrPos()), DATA_FONT_SIZE, MAIN_COLOR, data13);
  tft.print(String(host.getHeatPwr()), DATA_FONT_SIZE, MAIN_COLOR, data21);
  tft.print(host.getHydroLvlString(), DATA_FONT_SIZE, MAIN_COLOR, data22);
  tft.print(String(host.getCondTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data23);

  tft.print(captions.OUT_MTR_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label11);
  tft.print(captions.RET_MTR_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label12);
  tft.print(captions.COND_MTR_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label13);
  tft.print(captions.HEAT_PWR_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label21);
  tft.print(captions.HLVL_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label22);
  tft.print(captions.COND_TEMP_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label23);
}

void IMMega::drawDash2() {
  tft.paintBackground();
  tft.setColor(MAIN_COLOR);
  tft.fillRect(topBar);
  tft.fillRect(bottomBar);

  tft.print(captions.DASH2_HDR, HDR_FONT_SIZE, BACKGROUND_COLOR, topBar);
  tft.print(captions.ARROW_LEFT, HDR_FONT_SIZE, BACKGROUND_COLOR, topLeftRect);
  tft.print(captions.ARROW_RIGHT, HDR_FONT_SIZE, BACKGROUND_COLOR, topRightRect);

  drawDash2Data();
  drawBottomBar();
  
  prevActivePane = activePane;
  activePane = Panes::DASH2_PANE;
  refreshTimeout = DASHBOARD_TIMEOUT;

  refreshTime = millis();
  refreshRequired = false;
}

void IMMega::drawDash3Data() {
  tft.setColor(BACKGROUND_COLOR);
  tft.fillRect(IMRect(0, BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT-BAR_HEIGHT));

  tft.print(String(host.getExtAdj()), DATA_FONT_SIZE, MAIN_COLOR, data11);
  tft.print(String(host.getCondMtrAdj()), DATA_FONT_SIZE, MAIN_COLOR, data12);
  tft.print(String(host.getHeatAdj()), DATA_FONT_SIZE, MAIN_COLOR, data13);
  tft.print(host.getSwitchPosString(), DATA_FONT_SIZE, MAIN_COLOR, data21);
  tft.print(String(host.getRefluxRatio(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data22);

  tft.print(captions.EXT_ADJ_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label11);
  tft.print(captions.COND_ADJ_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label12);
  tft.print(captions.HEAT_ADJ_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label13);
  tft.print(captions.SW_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label21);
  tft.print(captions.RF_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label22);
}

void IMMega::drawDash3() {
  tft.paintBackground();
  tft.setColor(MAIN_COLOR);
  tft.fillRect(topBar);
  tft.fillRect(bottomBar);

  tft.print(captions.DASH3_HDR, HDR_FONT_SIZE, BACKGROUND_COLOR, topBar);
  tft.print(captions.ARROW_LEFT, HDR_FONT_SIZE, BACKGROUND_COLOR, topLeftRect);

  drawDash3Data();
  drawBottomBar();
  
  prevActivePane = activePane;
  activePane = Panes::DASH3_PANE;
  refreshTimeout = DASHBOARD_TIMEOUT;

  refreshTime = millis();
  refreshRequired = false;
}

void IMMega::drawKeyboardData(int num) {

}

void IMMega::drawKeyboard(int num) {
  tft.paintBackground();
  tft.setColor(MAIN_COLOR);
}

bool IMMega::refresh(bool full) {
  if (refreshRequired && (millis() - refreshTime >= refreshTimeout)) {
    if (full) {
      switch(activePane) {
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
        case ERROR_PANE:
          drawErrorsPane();
          break;
        case KEYBOARD:
          //drawKeyboard();
          break;
      }
    } else {
      switch(activePane) {
        case DASH1_PANE:
          drawDash1Data();
          break;
        case DASH2_PANE:
          drawDash2Data();
          break;
        case DASH3_PANE:
          drawDash3Data();
          break;
        case KEYBOARD:
          //drawKeyboardData();
          break;
        default:
          return refresh(true);
      }
    }
    refreshTime = millis();
    refreshRequired = false;
    return true;
  }
  return false;
}

bool IMMega::refresh() {
  return refresh(prevActivePane != activePane);
}

void IMMega::requireRefresh() {
  refreshRequired = true;
}

void IMMega::blink() {
  if (millis() - lastBlinkTime < blinkTimeout) {
    return;
  }

  if (blinkVisible) {
    tft.setColor(MAIN_COLOR);
  } else {
    tft.setColor(BACKGROUND_COLOR);
  }
  tft.fillRect(blinkRect);
  blinkVisible = !blinkVisible;
  lastBlinkTime = millis();
}
