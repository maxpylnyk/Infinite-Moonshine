#ifndef IM_DASHBOARD_1_H
#define IM_DASHBOARD_1_H

#include "IMDashboard.h"

class IMDashboard1 : public IMDashboard {
  public:
    IMDashboard1(IMTFT * tft, IMCaptions * captions, IMValuesHolder * host) 
      : IMDashboard(tft, captions, host) {};

    void refreshNumbers() {
      getTFT()->setColor(BACKGROUND_COLOR);
      getTFT()->fillRect(IMRect(0, BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT-BAR_HEIGHT));

      getTFT()->print(String(host->getSteamTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data11);
      getTFT()->print(String(host->getPipeTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data12);
      getTFT()->print(String(host->getAlcLvl()), DATA_FONT_SIZE, MAIN_COLOR, data13);
      getTFT()->print(String(host->getCalcTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data21);
      getTFT()->print(String(host->getEnvTemp(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data22);
      getTFT()->print(String((int)host->getPressure()), DATA_FONT_SIZE, MAIN_COLOR, data23);

      getTFT()->print(getCaptions()->STEAM_TEMP_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label11);
      getTFT()->print(getCaptions()->PIPE_TEMP_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label12);
      getTFT()->print(getCaptions()->ALC_LVL_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label13);
      getTFT()->print(getCaptions()->CALC_TEMP_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label21);
      getTFT()->print(getCaptions()->ENV_TEMP_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label22);
      getTFT()->print(getCaptions()->PRES_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label23);
    }

    void draw() {
      getTFT()->paintBackground();
      getTFT()->setColor(MAIN_COLOR);
      getTFT()->fillRect(topBar);
      getTFT()->fillRect(bottomBar);

      getTFT()->print(getCaptions()->DASH1_HDR, HDR_FONT_SIZE, BACKGROUND_COLOR, topBar);
      getTFT()->print(getCaptions()->ARROW_LEFT, HDR_FONT_SIZE, BACKGROUND_COLOR, topLeftRect);
      getTFT()->print(getCaptions()->ARROW_RIGHT, HDR_FONT_SIZE, BACKGROUND_COLOR, topRightRect);

      refreshNumbers();

      getTFT()->print(host->getStateString(), HDR_FONT_SIZE, BACKGROUND_COLOR, bottomBar);
      
      refreshTime = millis();
      refreshRequired = false;
    }

    void handleTouch() {

    }
    
};

#endif
