#include "IMMega.h"

IMMega::IMMega() {
  pinMode(LED_BUILTIN, OUTPUT);
  queue.reserve(QUEUE_LEN);
  debugText.reserve(DEBUG_TXT_LEN);
}
/**
 * Adds a key-value pair to the transfer queue.
 * Flushes queue if the buffer length reached.
 * 
 * @number is a key
 * @value is a value to transfer
 */
void IMMega::addToQueue(uint8_t number, String value) {
  String pair = String(number) + "\n" + value + "\n";
  int len = queue.length() + pair.length();

  if (len > bufferSize) {
    debugText += queue;
    port->print(queue);
    port->flush();
    queue = "";
    delayMicroseconds(bytesArrivalTime);
  }
  queue += pair;
}
/**
 * Flushes the transfer queue
 */
void IMMega::endQueue() {
  queue += String(endOfTransmission);
  port->print(queue);
  port->flush();
  debugText += "\n" + queue;
  debugPort->println("port output:");
  debugPort->println(debugText);
  queue = "";
  debugText = "";
  expectingConfirm = true;
}
/**
 *  Sends a full set of sensor readings and the ssr value if changed or by timeout.
 */
void IMMega::sendData() {
  debugPort->println("sendData() called");
  queue = String(dataSign);
  addToQueue(IMIndex::HEAT, String(savedValues.getHeat()));
  addToQueue(IMIndex::HYDRO_LEVEL, String(savedValues.getHydroLvl()));
  addToQueue(IMIndex::ALC_LEVEL, String(savedValues.getAlcLvl()));
  addToQueue(IMIndex::STEAM_TEMP, String(savedValues.getSteamTemp()));
  addToQueue(IMIndex::COND_TEMP, String(savedValues.getCondTemp()));
  addToQueue(IMIndex::PIPE_TEMP, String(savedValues.getPipeTemp()));
  addToQueue(IMIndex::ENV_TEMP, String(savedValues.getEnvTemp()));
  addToQueue(IMIndex::PRESSURE, String(savedValues.getPressure()));
  endQueue();
}
/** 
 * Receives a full set of values for the step motors, the ssr and useAlcMeter flag.
 * As a confirmation sends it back.
 */
void IMMega::receiveData() {
  transfering = true;

  while (port->available()) {
    int index = port->parseInt();
    long iTemp;
    float fTemp;

    switch(index) {
      case IMIndex::USE_ALC_METER :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (use alc meter) "+String(iTemp);
        savedValues.enableAlcMeter((bool)iTemp);
        break;
      case IMIndex::HEAT :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (heat) "+String(iTemp);
        savedValues.setHeat(iTemp);
        host.setHeat(iTemp);
        break;
      case IMIndex::OUT_MTR_POS :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (out mtr pos) "+String(iTemp);
        host.changeOutMtrPosOn(iTemp);
        break;
      case IMIndex::RET_MTR_POS :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (ret mtr pos) "+String(iTemp);
        host.changeRetMtrPosOn(iTemp);
        break;
      case IMIndex::COND_MTR_POS :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (cond mtr pos) "+String(iTemp);
        host.changeCondMtrPosOn(iTemp);
        break;
      case IMIndex::SW_POS :
        iTemp = port->parseInt();
        debugText += "\n"+String(index)+" (switch pos) "+String(iTemp);
        host.changeSwitchPosOn(iTemp);
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
    //errors.add(IMError::TRANSMISSION_CORRUPTED);
    debugText += "\ntransfer incomplete.";
    transfering = false;
  } else {
    port->println(confirmSign);
  }
}
/**
 * Moves step motors in a main loop
 */
bool IMMega::movingMotors() {
  if (outMtr.onPosition()) {
    if (retMtr.onPosition()) {
      if (condMtr.onPosition()) {
        swMtr.loop();
      } else {
        condMtr.loop();
      }
    } else {
      retMtr.loop();
    }
  } else {
    outMtr.loop();
  }
  bool movement = host.outMtrMoving();
  movement |= host.retMtrMoving();
  movement |= host.condMtrMoving();
  movement |= host.swMtrMoving();

  return movement;
}
/**
 * Updates sensor readings and transfers them if changed
 */
void IMMega::updateValues() {
  queue = String(dataSign);

  if (savedValues.getHeat() != host.getHeat()) {
    savedValues.setHeat(host.getHeat());
    addToQueue(IMIndex::HEAT, String(savedValues.getHeat()));
  }

  if (savedValues.getSteamTemp() != host.getSteamTemp()) {
    savedValues.setSteamTemp(host.getSteamTemp());
    addToQueue(IMIndex::STEAM_TEMP, String(savedValues.getSteamTemp()));
  }

  if (savedValues.getPipeTemp() != host.getPipeTemp()) {
    savedValues.setPipeTemp(host.getPipeTemp());
    addToQueue(IMIndex::PIPE_TEMP, String(savedValues.getPipeTemp()));
  }

  if (savedValues.getAlcLvl() != host.getAlcLvl()) {
    savedValues.setAlcLvl(host.getAlcLvl());
    addToQueue(IMIndex::ALC_LEVEL, String(savedValues.getAlcLvl()));
  }

  if (savedValues.getEnvTemp() != host.getEnvTemp()) {
    savedValues.setEnvTemp(host.getEnvTemp());
    addToQueue(IMIndex::ENV_TEMP, String(savedValues.getEnvTemp()));
  }

  if ((int)savedValues.getPressure() != (int)host.getPressure()) {
    savedValues.setPressure(host.getPressure());
    addToQueue(IMIndex::PRESSURE, String(savedValues.getPressure()));
  }

  if (savedValues.getHydroLvl() != host.getHydroLvl()) {
    savedValues.setHydroLvl(host.getHydroLvl());
    addToQueue(IMIndex::HYDRO_LEVEL, String(savedValues.getHydroLvl()));
  }

  if (savedValues.getCondTemp() != host.getCondTemp()) {
    savedValues.setCondTemp(host.getCondTemp());
    addToQueue(IMIndex::COND_TEMP, String(savedValues.getCondTemp()));
  }

  if (queue.equals(String(dataSign))) {
    queue = "";
  }
  if (queue.length()) {
    endQueue();
  }
}
/**
 * Transfers error codes
 */
void IMMega::sendErrors() {
  debugPort->print("errors:");
  queue = String(dataSign);

  for (int i = 0; i < errors.getCount(); i++) {
    addToQueue(IMIndex::ERROR_CODES, String(errors.get(i)));
    debugPort->print(" ");
    debugPort->print(errors.get(i));
  }
  if (queue.length()) {
    endQueue();
  }
  debugPort->println();
}
/**
 * Blinks with onboard LED
 */
void IMMega::blink() {
  if (millis() - lastBlinkTime < blinkTimeout) {
    return;
  }
  if (blinkVisible) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  blinkVisible = !blinkVisible;
  lastBlinkTime = millis();
}
/**
 * Initializes sensors
 */
bool IMMega::init() {
  bool result = true;

  timer.start();

  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);

  debugPort = &Serial;
  debugPort->begin(usbSpeed);

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

  debugPort->print("initializing barometer.. ");

  if (bar.init()) {
    debugPort->println("done in "+String(timer.check())+" ms");
  } else {
    errors.add(IMError::NO_BAR);
    debugPort->println("failed");
    timer.check();
    result = false;
  }
  
  debugPort->print("initializing serial interface.. ");
  port = &Serial2;
  port->begin(serialSpeed);
  debugPort->println("done in "+String(timer.check())+" ms");
  /*
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
  } else {
    debugPort->println("system initialization failure");
  }

  return result;
}
/**
 * Main cycle
 */
void IMMega::loop() {
  if (movingMotors()) {
    return;
  }
  if (!errors.isEmpty()) {
    if (errors.contains(IMError::TRANSMISSION_CORRUPTED)) {
      blink();
    }
    if (!errorsPrinted) {
      sendErrors();
      errorsPrinted = true;
    }
    return;
  } else {
    errorsPrinted = false;
  }
  if (host.collectValues(savedValues.useAlcMeter())) {
    updateValues();
    host.prepareToCollect(savedValues.useAlcMeter());
  }
}
/**
 * Sends a callsign
 */
void IMMega::sendCallsign() {
  if (initialize) {
    callsign = initSign;
  } else {
    callsign = onlineSign;
  }
  port->println(callsign);
}
/**
 * Receives a callsign
 */
void IMMega::receiveCallsign() {
  char message = port->read();

  debugText = "\nincoming callsign: "+String(message);

  switch(message) {
    case confirmSign:
      if (!expectingConfirm) {
        debugText += " unexpected";
      }
      debugText += " confirmation received.";
      break;
    case initSign:
      if (callsign == onlineSign) {
        debugText += "\nopi blackout. sending data:";
        sendData();
      } else {
        debugText += "\npower on.";
        sendCallsign();
        //sendData();
        initialize = false;
      }
      break;
    case onlineSign:
      debugText += "\nsending response: "+String(callsign);
      sendCallsign();
      break;
    case restartSign:
      debugText += "\nmega blackout. receiving data:";
      receiveData();
      break;
    case dataSign:
      receiveData();
      break;
    default:
      //errors.add(IMError::TRANSMISSION_CORRUPTED);
      debugText += "\nunknown callsign. transmission corrupted error.";
      //repeat transfer, attempts += 1; then if fails -> error
  }
  debugPort->println(debugText);
}
