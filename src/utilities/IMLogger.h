#ifndef IM_LOGGER_H
#define IM_LOGGER_H

#include "Arduino.h"
#include "utilities/IMTime.h"

typedef enum {
  INFO = "INFO",
  ERROR = "ERROR"
} IMLogLevel;

class IMLogger {
  private:
    IMTime timer;

    String toString(message, IMLogLevel level);
    void print(String message);

  public:
    IMLogger();

    void info(String message);
    void error(String message);

};

#endif
