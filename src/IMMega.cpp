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
  disableWatchdog();

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
  if (!DISABLE_ALC_METER) {
    debugPort->print("initializing alcohol sensor.. ");

    if (alc.init()) {
      debugPort->println("done in "+String(timer.check())+" ms");
    } else {
      errors.add(IMError::NO_ALC);
      debugPort->println("failed");
    timer.check();
      result = false;
    }
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
  } else {
    debugPort->println("system initialization failure");
    printErrors();
    drawErrorsPane();
  }

  return result;
}

void IMMega::loop() {
  restartWatchdog();
  /*
  if (millis() - responseTime >= callsignTimeout) {
    restartOther();
    responseTime = millis();
  }
  */
  if (!errors.isEmpty()) {
    if (!handleErrors()) {
      //printErrors();

      if (activePane != ERROR_PANE) {
        drawErrorsPane();//refresh errors list
      }
    }
  }
  moveMotors();
  
  if (host.collectValues()) {
    //write to current session, check if changed
    //if data changed -> sendData() and refresh dashes partly
    //logData(), send to logic
    if (activePane == DASH1_PANE 
    || activePane == DASH2_PANE 
    || activePane == DASH3_PANE
    || activePane == FRONT_PANE) {
      requireRefresh();
    }
    host.prepareToCollect();//place after refresh
  }
  handleTouch();
  refresh();
  blink();
}

void IMMega::debug() {
  //hlvl.debug();
  //delay(2000);
}

void IMMega::moveMotors() {
  outMtr.loop();
  retMtr.loop();
  condMtr.loop();
  swMtr.loop();
}

bool IMMega::handleErrors() {
  bool result = false;
  //todo reconnect sensors
  return result;
}

void IMMega::printErrors() {
  uint8_t count = errors.getCount();

  debugPort->println("errors count: "+String(count));

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
  addToQueue(LogIndex::STATE, String(session.getState()));
  addToQueue(LogIndex::PAUSE, String(isPaused()));
  addToQueue(LogIndex::COND_MTR, String(session.getCondMtrPos()));
  addToQueue(LogIndex::COND_MTR_ADJ, String(session.getCondMtrAdj()));
  addToQueue(LogIndex::SW, String(session.getSwitchPos()));
  addToQueue(LogIndex::HEAT, String(session.getHeatPwr()));
  addToQueue(LogIndex::HEAT_ADJ, String(session.getHeatAdj()));
  addToQueue(LogIndex::RF, String(session.getRefluxRatio()));
  addToQueue(LogIndex::OUT_MTR, String(session.getOutMtrPos()));
  addToQueue(LogIndex::RET_MTR, String(session.getRetMtrPos()));
  addToQueue(LogIndex::EXT_ADJ, String(session.getExtMtrAdj()));
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
      case LogIndex::STATE :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (state) "+String(iTemp);
        session.setState(iTemp);
        break;
      case LogIndex::PAUSE :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (pause) "+String(iTemp);
        setManualPause(iTemp);
        break;
      case LogIndex::ERROR_CODES :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (error) "+String(iTemp);
        errors.add(iTemp);
        break;
      case LogIndex::COND_MTR :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (cond mtr pos) "+String(iTemp);
        session.setCondMtrPos(iTemp);
        host.setCondCurPos(iTemp);
        break;
      case LogIndex::COND_MTR_ADJ :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (cond mtr adj) "+String(iTemp);
        session.setCondMtrAdj(iTemp);
        host.setCondMtrAdj(iTemp);
        break;
      case LogIndex::SW :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (switch pos) "+String(iTemp);
        session.setSwitchPos(iTemp);
        host.setSwCurPos(iTemp);
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
      case LogIndex::OUT_MTR :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (out mtr pos) "+String(iTemp);
        session.setOutMtrPos(iTemp);
        host.setOutCurPos(iTemp);
        break;
      case LogIndex::RET_MTR :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (ret mtr pos) "+String(iTemp);
        session.setRetMtrPos(iTemp);
        host.setRetCurPos(iTemp);
        break;
      case LogIndex::EXT_ADJ :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (ext adj) "+String(iTemp);
        session.setExtMtrAdj(iTemp);
        host.setExtAdj(iTemp);
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
    host.setOutMtrPos(editValue);
  }
  if (editLabel == captions.RET_MTR_LBL) {
    host.setRetMtrPos(editValue);
  }
  if (editLabel == captions.COND_MTR_LBL) {
    host.setCondMtrPos(editValue);
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
    host.setCondMtrAdj(editValue);
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
            drawKeyboard(host.getOutMtrPos(), captions.OUT_MTR_LBL);
          }
          if (slot12.hasPoint(touch)) {
            drawKeyboard(host.getRetMtrPos(), captions.RET_MTR_LBL);
          }
          if (slot13.hasPoint(touch)) {
            drawKeyboard(host.getCondMtrPos(), captions.COND_MTR_LBL);
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
            drawKeyboard(host.getCondMtrAdj(), captions.COND_ADJ_LBL);
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
        //drawFrontPane();
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
    //prevActivePane = activePane;
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

  tft.print(String(captions.getStateString(session.getState())), HDR_FONT_SIZE, BACKGROUND_COLOR, bottomBar);
}

void IMMega::drawPrevPane() {
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

  if (session.isActive()) {
    tft.print(captions.ABORT_SESSION, HDR_FONT_SIZE, BACKGROUND_COLOR, topLeftRect);
    if (MANUAL_MODE) {
      tft.print(captions.PAUSE_SESSION, HDR_FONT_SIZE, BACKGROUND_COLOR, topL2Rect);
    }
  } else {
    tft.print(captions.NEW_SESSION, HDR_FONT_SIZE, BACKGROUND_COLOR, topLeftRect);
  }
  tft.print(captions.INFO, HDR_FONT_SIZE, BACKGROUND_COLOR, topRightRect);

  tft.printNum(timer.getTime(), timeRect);
  //tft.print("Тип сырья объём", 2, MAIN_COLOR, srcBar);
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
  tft.setColor(MAIN_COLOR);
  tft.setFontSize(DATA_FONT_SIZE);

  tft.print(String(host.getOutMtrPos()), data11);
  tft.print(String(host.getRetMtrPos()), data12);
  tft.print(String(host.getCondMtrPos()), data13);
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
  tft.setColor(MAIN_COLOR);
  tft.setFontSize(DATA_FONT_SIZE);

  tft.print(String(host.getExtAdj()), data11);
  tft.print(String(host.getCondMtrAdj()), data12);
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
  refreshTimeout = 0;

  refreshTime = millis();
  refreshRequired = false;
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
          drawKeyboard(editValue, editLabel);
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
          drawKeyboardData();
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

void IMMega::printDebugText() {
  tft.paintBackground();
  tft.print(debugText, ERR_FONT_SIZE, TEXT_COLOR, 0, SCR_HEIGHT);
}
