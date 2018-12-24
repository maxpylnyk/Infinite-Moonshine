#ifndef IM_LOGGER_H
#define IM_LOGGER_H

#include "Arduino.h"
#include "IMTime.h"

class IMLogger {
  private:
    IMTime timer;

    enum IMLogLevel {
      INFO = "INFO",
      ERROR = "ERROR"
    };

    String toString(message, IMLogLevel level);
    void print(String message);

  public:
    IMLogger();

    void info(String message);
    void error(String message);

};

#endif
