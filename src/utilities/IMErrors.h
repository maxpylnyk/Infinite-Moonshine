#ifndef IM_ERRORS_H
#define IM_ERRORS_H

#include "stdint.h"

typedef enum IMError : uint8_t {
  NO_ERROR = 0,
  OVERFLOW,//h
  NO_HLVL,
  NO_CONNECTION,
  NO_SD_CARD,
  NO_SD_SPACE,
  NO_OUT_MTR,
  NO_RET_MTR,
  NO_COND_MTR,
  NO_SW,
  NO_ALC,
  NO_BAR,
  NO_RTC,
  NO_STEAM_TRM,
  NO_PIPE_TRM,
  NO_COND_TRM,
  NO_ENV_TRM,
  NO_HEAT,
  NANO_BLACKOUT,//h
  MEGA_BLACKOUT,//h
  TRANSMISSION_CORRUPTED,
  NO_LOG_DIR,
  ERRORS_COUNT
};

class IMErrors {
  private:
    uint8_t count = 0;
    uint8_t errors[IMError::ERRORS_COUNT];

  public:
    IMErrors();

    bool add(uint8_t);
    void clear();
    bool contains(uint8_t);
    bool remove(uint8_t);
    bool isEmpty();
    uint8_t getCount();
    uint8_t get(uint8_t index);

};

#endif
