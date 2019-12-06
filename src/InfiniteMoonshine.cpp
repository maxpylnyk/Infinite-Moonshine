#include "InfiniteMoonshine.h"

InfiniteMoonshine::InfiniteMoonshine(int rstPin) : rstPin(rstPin) {
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

void InfiniteMoonshine::initWatchdog() {
  wdt_disable();
  wdt_enable(rstWdtDelay);
  wtdRstTime = millis();
}

void InfiniteMoonshine::disableWatchdog() {
  wdt_disable();
}

void InfiniteMoonshine::restartWatchdog() {
  if (millis() - wtdRstTime >= watchdogTimeout) {
    wdt_reset();
  }
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
  callsignReceived = false;
  waitingTimer.start();
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
  debugText += "\n" + queue;
  queue = "";
}

float InfiniteMoonshine::calculateTemp(float pressure) {
  return 0.038 * pressure + 49.27;
}
