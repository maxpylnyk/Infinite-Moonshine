#ifndef IM_LOGGER_H
#define IM_LOGGER_H

#include "Arduino.h"
//#include "utilities/IMTimer.h"
#include "utilities/IMConstants.h"
#include "utilities/IMErrors.h"
//#include "utilities/IMFile.h"
//#include "SdFat.h"
//#include "SPI.h"

typedef enum LogEntry : char {
  STATE_INIT = '<',
  STATE_SUMMARY = '>',
  SESSION_INIT = 'i',
  SESSION_SUMMARY = 'd',
  USER_ACTION = 'u',
  ENTRY = '@',
  COMMENT = '#'
};

class IMLogger {
  private:
    static const uint8_t lineLen = 128;
    static const float megabyteMultiplier = 0.001024;
    char * logDirPath = "/im/log/";
    float avgLogSize;
    //IMTimer timer;
    char * filePath;
    //SdFat sd;
    IMErrors * errors;

    //bool enoughSpace();
    void writeHeader();
    //void searchFS();
    void setAvgSizeMB(float);
    float getAvgSizeMB();

  public:
    IMLogger();
    IMLogger(String fileName);

    bool init();
    bool println(String);
    void setFileName(String);
    void setErrorList(IMErrors*);

};

#endif
