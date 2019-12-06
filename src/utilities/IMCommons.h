#ifndef IM_COMMONS_H
#define IM_COMMONS_H

#include <stdint.h>

#define FLOAT_PRECISION           3
#define DISABLE_ALC_METER         1
#define DEBUG_MODE                1
#define MANUAL_MODE               1
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
const int SSR_PIN       = 45;
const int TRM_PIN       = 47;

const int DATA_PRECISION = 2;
const int HEIGHT_MULT = 7;
const int WIDTH_MULT = 6;
const int TEXT1_HEIGHT = HEIGHT_MULT;
const int TEXT2_HEIGHT = HEIGHT_MULT * 2;
const int PLAIN_FONT_SIZE = 2;
const int NUM_FONT_SIZE = 6;
const int LBL_FONT_SIZE = 1;
const int DATA_FONT_SIZE = 3;
const int ERR_FONT_SIZE = 1;
const int HDR_FONT_SIZE = 2;
const int SCR_HEIGHT = 240;
const int SCR_WIDTH = 320;
const int BAR_HEIGHT = 42;
const int DASH_SLOT_HEIGHT = (SCR_HEIGHT - 2 * BAR_HEIGHT) / 2;
const int DASH_SLOT_WIDTH = SCR_WIDTH / 3;
const int DASH_LBL_HEIGHT = LBL_FONT_SIZE * HEIGHT_MULT;
const int DASH_DATA_HEIGHT = DASH_SLOT_HEIGHT - DASH_LBL_HEIGHT;
const int BTN_WIDTH = 50;
const int KEY_WIDTH = SCR_WIDTH / 5;
const int KEY_HEIGHT = SCR_HEIGHT / 4; 

const uint16_t MAIN_COLOR        = 0x97fc;
const uint16_t MAIN_COLOR_FLAT   = 0x3b4c;
const uint16_t HEAT_COLOR        = 0xffa0;
const uint16_t STAB_COLOR        = 0xfba0;
const uint16_t HEAD_COLOR        = 0xf800;
const uint16_t AROMA_COLOR       = 0xf81f;
const uint16_t BODY_COLOR        = 0xffff;
const uint16_t TAIL_COLOR        = 0x045f;
const uint16_t BACKGROUND_COLOR  = 0x0000;

const uint16_t TEXT_COLOR        = MAIN_COLOR;
const uint16_t ERROR_COLOR       = STAB_COLOR;

const unsigned long SENSORS_UPD_TIMEOUT = (unsigned long) 5 * 1000;
const unsigned long ALC_TIMEOUT = (unsigned long) 30 * 60 * 1000;
const unsigned long TRM_TIMEOUT = SENSORS_UPD_TIMEOUT;
const unsigned long BAR_TIMEOUT = SENSORS_UPD_TIMEOUT;
const unsigned long HLVL_TIMEOUT = 0;

const unsigned long FRONT_PANE_TIMEOUT = 60000;
const unsigned long DASHBOARD_TIMEOUT = SENSORS_UPD_TIMEOUT;

const unsigned long KEY_DIGIT_LIMIT = 99999;

typedef enum IMLevel : uint8_t {
  LO      = 0x0,
  OK      = 0x1,
  HI      = 0x3,
  OVR     = 0x7
} IMLevel;

typedef enum Panes : uint8_t {
  INIT_PANE = 0,
  ERROR_PANE,
  FRONT_PANE,
  DASH1_PANE,
  DASH2_PANE,
  DASH3_PANE,
  KEYBOARD,
  CONFIRM_DIALOG,
  LOG_PANE,
  PREF_PANE,
  PLOT_PANE
} Panes;

typedef enum LogIndex : uint8_t {
  SESSION_NAME = 1,
  STATE,
  PAUSE,
  HYDRO_LEVEL,
  ALC_LEVEL,
  STEAM_TEMP,
  TABLE_TEMP,
  COND_TEMP,
  PIPE_TEMP,
  ENV_TEMP,
  PRESSURE,
  COND_MTR,
  COND_MTR_ADJ,
  SW,
  HEAT,
  HEAT_ADJ,
  RF,
  OUT_MTR,
  RET_MTR,
  EXT_ADJ,
  ERROR_CODES
} LogIndex;

typedef enum SrcType : uint8_t {
  SUGAR = 0,
  GRAIN,
  GRAPE,
  APPLE,
  APRICOT,
  PEACH,
  PLUM,
  CHERRY
} SrcType;

typedef enum Pause : uint8_t {
  RESUME = 0,
  CONTROL,
  MANUAL
} Pause;

typedef enum Board : uint8_t {
  MEGA = 0,
  NANO
} Board;

typedef enum Language : uint8_t {
  ENGLISH = 0,
  RUSSIAN
} Language;

typedef enum State : int8_t {
  FINISH_STATE = -3,
  CANCEL_STATE,
  ERROR_STATE,
  STAND_BY_STATE,
  HEAT_STATE,
  STAB_STATE,
  HEAD_STATE,
  PRE_BODY_STATE,
  BODY_STATE,
  PRE_TAIL_STATE
} State;

#endif
