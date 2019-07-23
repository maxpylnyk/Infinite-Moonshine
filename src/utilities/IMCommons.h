#ifndef IM_COMMONS_H
#define IM_COMMONS_H

#define FLOAT_PRECISION  3

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
};

typedef enum SrcType : uint8_t {
  SUGAR = 0,
  GRAIN,
  GRAPE,
  APPLE,
  PEACH,
  CHERRY
};

typedef enum Pause : uint8_t {
  RESUME = 0,
  CONTROL,
  MANUAL
};

typedef enum Board : uint8_t {
  MEGA = 0,
  NANO
};

typedef enum Language : uint8_t {
  ENGLISH = 0,
  RUSSIAN
};

typedef enum PinMap : uint8_t {
  NANO_RST  = A7,
  ALC_HEAT  = A10,
  ALC_DATA  = A11,
  HLVL_OUT  = A12,
  HLVL_LO   = A13,
  HLVL_HI   = A14,
  HLVL_OVR  = A15,
  SD_CS     = 10,
  MTR1_1    = 22,
  MTR1_2    = 23,
  MTR1_3    = 24,
  MTR1_4    = 25,
  MTR2_1    = 26,
  MTR2_2    = 27,
  MTR2_3    = 28,
  MTR2_4    = 29,
  MTR3_1    = 30,
  MTR3_2    = 31,
  MTR3_3    = 32,
  MTR3_4    = 33,
  MTR4_1    = 34,
  MTR4_2    = 35,
  MTR4_3    = 36,
  MTR4_4    = 37,
  MEGA_RST  = 43,
  SSR       = 45,
  TRM       = 47,
};

#endif
