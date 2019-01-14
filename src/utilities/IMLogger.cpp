#include "IMLogger.h"

IMLogger::IMLogger() {
  fileName = timer.getFileName();
}

IMLogger::IMLogger(String fileName) : fileName(fileName) {}

bool IMLogger::init() {
  //check free space
  return SD.begin(SD_CS);
}

bool IMLogger::print(String line) {
  logFile = SD.open(fileName, FILE_WRITE);

  if (logFile) {
    logFile.println(line);
    logFile.close();
    return true;
  }
  return false;
}