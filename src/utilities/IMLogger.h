#ifndef IM_LOGGER_H
#define IM_LOGGER_H

#include "Arduino.h"
#include "utilities/IMTimer.h"
#include <SD.h>

class IMLogger {
  private:
    static const int SD_CS = 10;

    IMTimer timer;
    String fileName;
    File logFile;

  public:
    IMLogger();
    IMLogger(String fileName);

    bool init();
    bool print(String);

};

#endif
