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
      NO_STEAM_TRM = "Steam thermometer disconnected";
      NO_PIPE_TRM = "Pipe thermometer disconnected";
      NO_COND_TRM = "Condenser thermometer disconnected";
      NO_ENV_TRM = "Environment thermometer disconnected";
      NO_HEAT = "No heat";
      NANO_BLACKOUT = "Control MCU blackout";
      MEGA_BLACKOUT = "Main MCU blackout";
      TRANSMISSION_CORRUPTED = "Transmission corrupted";
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
      NO_STEAM_TRM = "Паровой термометр не подключён";
      NO_PIPE_TRM = "Царговый термометр не подключён";
      NO_COND_TRM = "Термометр охлаждения не подключён";
      NO_ENV_TRM = "Атмосферный термометр не подключён";
      NO_HEAT = "Нет нагрева";
      NANO_BLACKOUT = "Контрольный МК отключился";
      MEGA_BLACKOUT = "Главный МК отключился";
      TRANSMISSION_CORRUPTED = "Повреждение передачи данных";
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
    char * NO_STEAM_TRM;
    char * NO_PIPE_TRM;
    char * NO_COND_TRM;
    char * NO_ENV_TRM;
    char * NO_HEAT;
    char * NANO_BLACKOUT;
    char * MEGA_BLACKOUT;
    char * TRANSMISSION_CORRUPTED;

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

};

#endif
