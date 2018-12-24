const int interruptStartIndex = 0;
const int interruptEndIndex = 1;

bool masterWasRestarted;
bool interrupted;
bool dataTransfer;

bool dataFromMaster;
bool dataFromSlave;

const uint8_t onlineMask    = 0x01;
const uint8_t transferMask  = 0x02;
const uint8_t restartMask   = 0x04;
const uint8_t dataSize = 50;//??
uint8_t dataIndex;
uint8_t data[dataSize];

void setup() {
  Serial.begin(9600);
  initSlaveSPI();
  dataTransfer = false;
}

void loop() {

}

void initSlaveSPI() {
  initSlaveMode();
  initInterrupts();
}

void initSlaveMode() {
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
}

void initInterrupts() {
  SPCR |= _BV(SPIE);
  attachInterrupt(interruptStartIndex, interruptStart, FALLING);
  attachInterrupt(interruptEndIndex, interruptEnd, RISING);
}

ISR(SPI_STC_vect) {
  interruptRoutine();
}

void interruptStart() {
  interrupted = true;
}

void interruptRoutine() {
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

void interruptEnd() {
  interrupted = false;
}

void readCallsign(uint8_t callsign) {
  if (callsign & onlineMask) {
    //log master online
  } else {
    restartMaster();
  }
  if (callsign & transferMask) {
    dataFromMaster = true;
  }
  if (callsign & restartMask) {
    //slave was restarted
  }
}

uint8_t getCallsign() {
  uint8_t callsign = 0;

  callsign |= onlineMask;

  if (dataFromSlave) {
    callsign |= transferMask;
  }
  if (masterWasRestarted) {
    callsign |= restartMask;
    masterWasRestarted = false;
  }
  return callsign;
}


void readData() {
  //search and run master commands from array
}

void writeData() {
  //collect data into array
  dataIndex = 0;
}

void restartMaster() {
  //restast and send checkpoint data
  masterWasRestarted = true;
}
