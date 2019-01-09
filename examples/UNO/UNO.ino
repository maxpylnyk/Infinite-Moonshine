#include <SPI.h>

#define noop ((void) 0)
#define wait noop noop noop noop noop noop noop noop noop noop noop 

const uint8_t onlineMask    = 0x01;
const uint8_t transferMask  = 0x02;
const uint8_t restartMask   = 0x04;

const uint8_t megaSlavePin = 4;
const uint8_t dataSize = 44;
const int interruptStartIndex = 0;
const int interruptEndIndex = 1;

bool slaveWasRestarted;
bool dataTransfer;

bool dataFromMaster;
bool dataFromSlave;

uint8_t dataIndex;
uint8_t data[dataSize];

SPISettings settings(4000000, MSBFIRST, SPI_MODE0);

void setup() {
  Serial.begin(9600);
  initMasterSPI();
}

void loop() {

}

void initMasterSPI() {
  pinMode(megaSlavePin, OUTPUT);
  digitalWrite(megaSlavePin, HIGH);
  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin();
}

void checkSlave() {
  beginTransfer();
  readCallsign(trasferByte(getCallsign()));
  endTransfer();
}

uint8_t transferByte(uint8_t message) {
  uint8_t answer = SPI.transfer(message);
  //wait;
  delayMicroseconds(20);
  return answer;
}uint8_t trasferByte(uint8_t message) {
  uint8_t answer = SPI.transfer(message);
  //wait;
  delayMicroseconds(20);
  return answer;
}

void transferData() {
  beginTransfer();

  for (int i = 0; i < dataSize; i++) {
    data[i] = transferByte(data[i]);
  }
  endTransfer();
}

void beginTransfer() {
  //SPI.usingInterrupt(interruptStartIndex);
  //SPI.usingInterrupt(interruptEndIndex);
  SPI.beginTransaction(settings);
  digitalWrite(megaSlavePin, LOW);
}

void endTransfer() {
  digitalWrite(megaSlavePin, HIGH);
  SPI.endTransaction();
}

void readCallsign(uint8_t callsign) {
  if (callsign & onlineMask) {
    //log slave online
    Serial.println("slave online");
  } else {
    restartSlave();
  }
  if (callsign & transferMask) {
    dataFromSlave = true;
  }
  if (callsign & restartMask) {
    //master was restarted
    Serial.println("master was restarted");
  }
}

uint8_t getCallsign() {
  uint8_t callsign = 0;

  callsign |= onlineMask;

  if (dataFromMaster) {
    callsign |= transferMask;
  }
  if (slaveWasRestarted) {
    callsign |= restartMask;
    slaveWasRestarted = false;
  }
  return callsign;
}

void restartSlave() {
  //restast and send checkpoint data
  slaveWasRestarted = true;
}
