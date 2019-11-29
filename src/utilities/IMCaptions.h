#ifndef IM_CAPTIONS_H
#define IM_CAPTIONS_H

#include "utilities/IMCommons.h"

class IMCaptions {
  private:
    Language locale;

    void initEnglishCaptions() {
      NO_ERROR = "No errors found";
      OVERFLOW = "Extraction node overflow";
      NO_HLVL = "Hydrolevel disconnected";
      NO_CONNECTION = "No connection with control MCU";
      NO_SD_CARD = "SD card not found";
      NO_SD_SPACE = "No free space left on SD card";
      NO_OUT_MTR = "Output tap motor disconnected";
      NO_RET_MTR = "Return tap motor disconnected";
      NO_COND_MTR = "Condenser tap motor disconnected";
      NO_SW = "Switch motor disconnected";
      NO_ALC = "Alcohol sensor disconnected";
      NO_BAR = "Barometer disconnected";
      NO_RTC = "Clock disconnected";
      NO_TRM = "Thermometers disconnected";
      NO_STEAM_TRM = "Steam thermometer disconnected";
      NO_PIPE_TRM = "Pipe thermometer disconnected";
      NO_COND_TRM = "Condenser thermometer disconnected";
      NO_ENV_TRM = "Environment thermometer disconnected";
      NO_HEAT = "No heat";
      NANO_BLACKOUT = "Control MCU blackout";
      MEGA_BLACKOUT = "Main MCU blackout";
      TRANSMISSION_CORRUPTED = "Transmission corrupted";
      NO_LOG_DIR = "Log dir unavailable";
      STARTING = "Starting..";
      WELCOME = "Welcome!";
      ERRORS = "Errors:";
      STEAM_TEMP_LBL = "steam, *C";
      PIPE_TEMP_LBL = "2/3 pipe, *C";
      ALC_LVL_LBL = "alcohol";
      CALC_TEMP_LBL = "calc, *C";
      ENV_TEMP_LBL = "room, *C";
      PRES_LBL = "pres., mm Hg";
      OUT_MTR_LBL = "out flow, ml/h";
      RET_MTR_LBL = "ret. flow, ml/h";
      COND_MTR_LBL = "cond. flow, ml/h";
      HEAT_PWR_LBL = "heater, %";
      HLVL_LBL = "hydrolevel";
      COND_TEMP_LBL = "cond, *C";
      EXT_ADJ_LBL = "extr. adj.";
      COND_ADJ_LBL = "cond. adj.";
      HEAT_ADJ_LBL = "heat. adj.";
      SW_LBL = "switch";
      RF_LBL = "rf. ratio";

      STAND_BY_LBL = "STANDING BY";
      HEAT_LBL = "HEATING";
      STAB_LBL = "STABILIZING";
      HEAD_LBL = "EXTRACTING HEADS";
      PRE_BODY_LBL = "PRE BODY";
      BODY_LBL = "EXTRACTING BODY";
      PRE_TAIL_LBL = "PRE TAIL";
      FINISH_LBL = "FINISHED";
      CANCEL_LBL = "CANCELED";
      ERROR_LBL = "ERROR";
    }

    void initRussianCaptions() {
      NO_ERROR = "Ошибки не обнаружены";
      OVERFLOW = "Переполнение узла отбора";
      NO_HLVL = "Гидроуровень не подключён";
      NO_CONNECTION = "Нет соединения с контрольным МК";
      NO_SD_CARD = "Карта памяти отсутвует";
      NO_SD_SPACE = "На карте памяти нет свободного места";
      NO_OUT_MTR = "Мотор крана отбора не подключён";
      NO_RET_MTR = "Мотор крана возврата не подключён";
      NO_COND_MTR = "Мотор крана холодильника не подключён";
      NO_SW = "Мотор сортировочного узла не подключён";
      NO_ALC = "Датчик алкоголя не подключён";
      NO_BAR = "Барометр не подключён";
      NO_RTC = "Часы не подключены";
      NO_TRM = "Термометры не подключены";
      NO_STEAM_TRM = "Паровой термометр не подключён";
      NO_PIPE_TRM = "Царговый термометр не подключён";
      NO_COND_TRM = "Термометр охлаждения не подключён";
      NO_ENV_TRM = "Атмосферный термометр не подключён";
      NO_HEAT = "Нет нагрева";
      NANO_BLACKOUT = "Контрольный МК отключился";
      MEGA_BLACKOUT = "Главный МК отключился";
      TRANSMISSION_CORRUPTED = "Повреждение передачи данных";
      NO_LOG_DIR = "Каталог журналов недоступен";
      STARTING = "Запуск..";
      WELCOME = "Что варим?";
      ERRORS = "Ошибки:";
      STEAM_TEMP_LBL = "пар, *С";
      PIPE_TEMP_LBL = "2/3 царги, *С";
      ALC_LVL_LBL = "алкоголь";
      CALC_TEMP_LBL = "теор. пар, *С";
      ENV_TEMP_LBL = "комната, *С ";
      PRES_LBL = "давл., мм.р.ст.";
      OUT_MTR_LBL = "отбор, мл/ч";
      RET_MTR_LBL = "возврат, мл/ч";
      COND_MTR_LBL = "охл., мл/ч";
      HEAT_PWR_LBL = "нагрев, %";
      HLVL_LBL = "гидроуровень";
      COND_TEMP_LBL = "вода, *С";
      EXT_ADJ_LBL = "шаг отбора";
      COND_ADJ_LBL = "шаг охл.";
      HEAT_ADJ_LBL = "шаг нагрева";
      SW_LBL = "приёмник";
      RF_LBL = "фл. число";

      STAND_BY_LBL = "ПРОСТОЙ";
      HEAT_LBL = "НАГРЕВ";
      STAB_LBL = "СТАБИЛИЗАЦИЯ";
      HEAD_LBL = "ОТБОР ГОЛОВ";
      PRE_BODY_LBL = "ПОДГОЛОВНИКИ";
      BODY_LBL = "ОТБОР ТЕЛА";
      PRE_TAIL_LBL = "ПРЕДХВОСТ";
      FINISH_LBL = "ЗАКОНЧЕНО";
      CANCEL_LBL = "ОТМЕНЕНО";
      ERROR_LBL = "ОШИБКА";
    }

  public:
    char * NO_ERROR;
    char * OVERFLOW;
    char * NO_HLVL;
    char * NO_CONNECTION;
    char * NO_SD_CARD;
    char * NO_SD_SPACE;
    char * NO_OUT_MTR;
    char * NO_RET_MTR;
    char * NO_COND_MTR;
    char * NO_SW;
    char * NO_ALC;
    char * NO_BAR;
    char * NO_RTC;
    char * NO_TRM;
    char * NO_STEAM_TRM;
    char * NO_PIPE_TRM;
    char * NO_COND_TRM;
    char * NO_ENV_TRM;
    char * NO_HEAT;
    char * NANO_BLACKOUT;
    char * MEGA_BLACKOUT;
    char * TRANSMISSION_CORRUPTED;
    char * NO_LOG_DIR;

    char * STARTING;
    char * WELCOME;
    char * ERRORS;
    char * INFO = "i";
    char * NEW_SESSION = "+";
    char * PAUSE_SESSION = "||";
    char * ABORT_SESSION = "X";
    char * ARROW_LEFT = "<-";
    char * ARROW_RIGHT = "->";
    char * DASH1_HDR = "@ * *";
    char * DASH2_HDR = "* @ *";
    char * DASH3_HDR = "* * @";
    char * STEAM_TEMP_LBL;
    char * PIPE_TEMP_LBL;
    char * ALC_LVL_LBL;
    char * CALC_TEMP_LBL;
    char * ENV_TEMP_LBL;
    char * PRES_LBL;
    char * OUT_MTR_LBL;
    char * RET_MTR_LBL;
    char * COND_MTR_LBL;
    char * HEAT_PWR_LBL;
    char * HLVL_LBL;
    char * COND_TEMP_LBL;
    char * EXT_ADJ_LBL;
    char * COND_ADJ_LBL;
    char * HEAT_ADJ_LBL;
    char * SW_LBL;
    char * RF_LBL;

    char * STAND_BY_LBL;
    char * HEAT_LBL;
    char * STAB_LBL;
    char * HEAD_LBL;
    char * PRE_BODY_LBL;
    char * BODY_LBL;
    char * PRE_TAIL_LBL;
    char * FINISH_LBL;
    char * CANCEL_LBL;
    char * ERROR_LBL;

    IMCaptions(Language l = Language::ENGLISH) {
      locale = l;

      switch(locale) {
        case Language::ENGLISH :
          initEnglishCaptions();
          break;
        case Language::RUSSIAN :
          initRussianCaptions();
          break;
      } 
    }

    char * getStateString(State s) {
      switch(s) {
        case STAND_BY_STATE:
          return STAND_BY_LBL;
        case HEAT_STATE:
          return HEAT_LBL;
        case STAB_STATE:
          return STAB_LBL;
        case HEAD_STATE:
          return HEAD_LBL;
        case PRE_BODY_STATE:
          return PRE_BODY_LBL;
        case BODY_STATE:
          return BODY_LBL;
        case PRE_TAIL_STATE:
          return PRE_TAIL_LBL;
        case FINISH_STATE:
          return FINISH_LBL;
        case CANCEL_STATE:
          return CANCEL_LBL;
      }
      return ERROR_LBL;
    }

};

#endif
