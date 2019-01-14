#include "IMUno.h"

IMUno::IMUno() {}

bool IMUno::init() {
  if (DEBUG_MODE) {
    Serial.begin(9600);
  }
  Serial.println("initialize is "+String(initialize));
  currentState = STAND_BY_STATE;
  timer.start();
  initMasterSPI();
  Serial.println("spi init time "+String(timer.stop()));
  //wait for mega
  if (checkSlave()) {
    //make decision

  } else {
    Serial.println("error: slave disconnected");
    return false;
  }
  return true;
}

void IMUno::loop() {
  //refresh ui and wait for user input
}

void IMUno::debug() {
  //fill array and transfer
}

bool IMUno::readCallsign(uint8_t callsign) {
  bool result = true;

  dataFromMaster = false;
  dataFromSlave = false;

  switch(callsign & statusMask) {
    case 0b0000:
      Serial.println("MEGA offline");
      //try again. if no answer -> restartSlave();
      result = false;
      break;
    case 0b0001:
      Serial.println("MEGA online");
      //normal operation
      break;
    case 0b0011:
      Serial.println("transfer required");
      dataFromSlave = true;
      //normal operation. transfer data
      break;
    case 0b0111:
      Serial.println("UNO was restarted and transfer required");
      dataFromSlave = true;
      thisRestarted = true;
      //ask data (fill array with 0s and trasfer. read and apply) -> continue
      break;
    case 0b1011:
      Serial.println("MEGA just turned on and waiting for command");
      //if initialize == true -> read log -> transfer command (resume | stby)
      //if no log -> stby
      break;
    default:
      Serial.println("undefined callsign "+String(callsign & statusMask, BIN));
      result = false;
  }
  StateIndex i = getIndex(callsign);
  
  if (i != currentState) {
    currentState = i;
    //refresh ui
  }
  return result;
}

uint8_t IMUno::getCallsign() {
  uint8_t callsign = onlineMask;

  if (dataFromMaster) {//if master has commands
    callsign |= transferMask;
  }
  if (otherRestarted) {
    callsign |= restartMask;
  }
  if (initialize) {
    callsign |= initMask;
  }
  callsign |= currentState;

  return callsign;
}

void IMUno::restartSlave() {
  digitalWrite(RST_PIN, HIGH);
  Serial.println("restarting MEGA");
  delay(restartDelay);
  digitalWrite(RST_PIN, LOW);
  //send checkpoint data
  otherRestarted = true;
}

void IMUno::initMasterSPI() {
  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH);
  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin();
}

uint8_t IMUno::transferByte(uint8_t message) {
  uint8_t answer = SPI.transfer(message);
  //wait;
  delayMicroseconds(20);
  return answer;
}

bool IMUno::checkSlave() {
  bool result;

  beginTransfer();
  result = readCallsign(transferByte(getCallsign()));
  endTransfer();

  return result;
}

void IMUno::transferData() {
  beginTransfer();

  for (int i = 0; i < dataArraySize; i++) {
    data[i] = transferByte(data[i]);
  }
  endTransfer();
}

void IMUno::beginTransfer() {
  //SPI.usingInterrupt(interruptStartIndex);
  //SPI.usingInterrupt(interruptEndIndex);
  SPI.beginTransaction(settings);
  digitalWrite(SS_PIN, LOW);
}

void IMUno::endTransfer() {
  digitalWrite(SS_PIN, HIGH);
  SPI.endTransaction();
}
