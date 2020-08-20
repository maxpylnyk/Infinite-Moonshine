#ifndef IM_CONSTANTS_H
#define IM_CONSTANTS_H

#include <stdint.h>

#define FLOAT_PRECISION           3
#define DISABLE_ALC_METER         1
#define MANUAL_MODE               1
#define IGNORE_ERRORS             0
#define UNSTABLE_PRESSURE_REGION  0

const int NANO_RST_PIN  = 61;//A7 (54+num)
const int ALC_HEAT_PIN  = 64;//A10
const int ALC_DATA_PIN  = 65;//A11
const int HLVL_OUT_PIN  = 66;//A12
const int HLVL_LO_PIN   = 67;//A13
const int HLVL_HI_PIN   = 68;//A14
const int HLVL_OVR_PIN  = 69;//A15
const int SD_CS_PIN     = 10;
const int MTR1_1_PIN    = 22;
const int MTR1_2_PIN    = 23;
const int MTR1_3_PIN    = 24;
const int MTR1_4_PIN    = 25;
const int MTR2_1_PIN    = 26;
const int MTR2_2_PIN    = 27;
const int MTR2_3_PIN    = 28;
const int MTR2_4_PIN    = 29;
const int MTR3_1_PIN    = 30;
const int MTR3_2_PIN    = 31;
const int MTR3_3_PIN    = 32;
const int MTR3_4_PIN    = 33;
const int MTR4_1_PIN    = 34;
const int MTR4_2_PIN    = 35;
const int MTR4_3_PIN    = 36;
const int MTR4_4_PIN    = 37;
const int MEGA_RST_PIN  = 43;
const int SSR_PIN       = 3;
const int TRM_PIN       = 47;

const int DATA_PRECISION = 2;

const uint16_t QUEUE_LEN = 100;
const uint16_t DEBUG_TXT_LEN = 300;
const float FLEGMA_TEMP = 62.5;
const float TEMP_OFFSET = 0.5;

const unsigned long SENSORS_UPD_TIMEOUT = (unsigned long) 5 * 1000;
const unsigned long ALC_TIMEOUT = (unsigned long) 10 * 60 * 1000;
const unsigned long TRM_TIMEOUT = SENSORS_UPD_TIMEOUT;
const unsigned long BAR_TIMEOUT = SENSORS_UPD_TIMEOUT;
const unsigned long HLVL_TIMEOUT = 0;
const unsigned long COND_INERTION = (unsigned long) 2 * 60 * 1000;

typedef enum IMLevel : uint8_t {
  LO      = 0x0,
  OK      = 0x1,
  HI      = 0x3,
  OVR     = 0x7
} IMLevel;

typedef enum IMIndex : uint8_t {
  HYDRO_LEVEL = 1,
  ALC_LEVEL,
  USE_ALC_METER,
  STEAM_TEMP,
  TABLE_TEMP,
  COND_TEMP,
  PIPE_TEMP,
  ENV_TEMP,
  PRESSURE,
  HEAT,
  OUT_MTR_POS,
  RET_MTR_POS,
  COND_MTR_POS,
  SW_POS,
  ERROR_CODES
} LogIndex;

#endif
