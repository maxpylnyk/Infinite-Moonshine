#include "InfiniteMoonshine.h"

InfiniteMoonshine::InfiniteMoonshine(int rstPin) : rstPin(rstPin) {
  setSessionName(0);
  pinMode(LED_BUILTIN, OUTPUT);
}

uint8_t InfiniteMoonshine::isPaused() {
  if (MANUAL_MODE) {
    if (manualPause) {
      return manualPause;
    }
  }
  return pause;
}

void InfiniteMoonshine::setPause(uint8_t value) {
    pause = value;
}

void InfiniteMoonshine::setManualPause(uint8_t value) {
  if (MANUAL_MODE) {
    manualPause = value;
  }
}

uint8_t InfiniteMoonshine::getStateIndex() {
  return stateIndex;
}

void InfiniteMoonshine::setStateIndex(uint8_t value) {
  stateIndex = value;
  //индикатор для синхронизации.
  //в ручном режиме при семене этапа отправляется как запрос
  //если приходит такой же - смена подтверждена
  //если предыдущий - нет
}

uint32_t InfiniteMoonshine::getSessionName() {
  return sessionName;
}

void InfiniteMoonshine::setSessionName(uint32_t value) {
  sessionName = value;
}

void InfiniteMoonshine::initWatchdog() {
  /*
  wdt_disable();
  wdt_enable(rstWdtDelay);
  wtdRstTime = millis();
  */
}

void InfiniteMoonshine::restartWatchdog() {
  /*
  if (millis() - wtdRstTime >= watchdogTimeout) {
    wdt_reset();
  }
  */
}

void InfiniteMoonshine::restartOther() {
  digitalWrite(rstPin, HIGH);
  delay(rstPinDelay);
  digitalWrite(rstPin, LOW);
  otherRestarted = true;
  sendData();
}

void InfiniteMoonshine::sendCallsign() {
  if (initialize) {
    callsign = initSign;
  } else {
    callsign = onlineSign;
  }
  port->print(callsign);
  port->flush();
  responseTime = millis();
}

void InfiniteMoonshine::addToQueue(byte number, String value) {
  String pair = String(number) + " " + value + " ";
  int len = queue.length() + pair.length();

  if (len > bufferSize) {
    port->print(queue);
    port->flush();
    queue = "";
    delayMicroseconds(bytesArrivalTime);
  }
  queue += pair;
}

void InfiniteMoonshine::endQueue() {
  queue += String(endOfTransmission);
  port->print(queue);
  port->flush();

  queue = "";
}

float InfiniteMoonshine::calculateTemp(float pressure) {
  return 0.038 * pressure + 49.27;
}
