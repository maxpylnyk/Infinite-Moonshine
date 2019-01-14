#include "IMMega.h"

IMMega::IMMega() {}

bool IMMega::init() {
  if (DEBUG_MODE) {
    Serial.begin(9600);
  }
  Serial.println("initializing mega");
  state = &IMStandByState();
  timer.start();
  initSlaveSPI();
  Serial.println("spi init time "+String(timer.stop()));
  return true;
}

void IMMega::loop() {

}

void IMMega::debug() {

}

bool IMMega::readCallsign(uint8_t callsign) {
  bool result = true;

  dataFromMaster = false;
  dataFromSlave = false;

  switch(callsign & statusMask) {
    case 0b0000:
      Serial.println("UNO offline");
      //try again. if no answer -> restartMaster();
      result = false;
      break;
    case 0b0001:
      Serial.println("UNO online");
      //normal operation
      break;
    case 0b0011:
      Serial.println("transfer required");
      dataFromMaster = true;
      dataFromSlave = true;
      //normal operation. receive commands from master
      //search non-zero values in array and apply them
      break;
    case 0b0111:
      Serial.println("MEGA was restarted and transfer required");
      thisRestarted = true;
      dataFromMaster = true;
      //fill array with 0s, receive data and apply
      break;
    case 0b1001:
      Serial.println("UNO just turned on");

      //stby
      break;
    default:
      Serial.println("undefined case "+String(callsign & statusMask, BIN));
      result = false;
  }
  getIndex(callsign);//just compare, do nothing. MEGA controls state

  return result;
}

uint8_t IMMega::getCallsign() {
  uint8_t callsign = onlineMask;

  if (dataFromSlave) {
    callsign |= transferMask;
  }
  if (otherRestarted) {
    callsign |= restartMask;
  }
  if (initialize) {
    callsign |= initMask;
  }
  callsign |= state->getStateIndex();

  return callsign;
}

void IMMega::restartMaster() {
  digitalWrite(RST_PIN, HIGH);
  Serial.println("restarting UNO");
  delay(restartDelay);
  digitalWrite(RST_PIN, LOW);
  //send checkpoint data
  otherRestarted = true;
}

void IMMega::interruptRoutine() {
  byte message = SPDR;
  byte answer;

  if (dataTransfer) {
    answer = data[dataIndex];
    data[dataIndex] = message;
    dataIndex += 1;
  } else {
    readCallsign(message);
    answer = getCallsign();
  }
  SPDR = answer;
}

void IMMega::initSlaveMode() {
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
}

void IMMega::initInterrupts() {
  SPCR |= _BV(SPIE);
}

void IMMega::initSlaveSPI() {
  initSlaveMode();
  initInterrupts();
}
