#ifndef IM_DASHBOARD_3_H
#define IM_DASHBOARD_3_H

#include "IMDashboard.h"

class IMDashboard3 : public IMDashboard {
  public:
    IMDashboard3(IMTFT * tft, IMCaptions * captions, IMValuesHolder * host) 
      : IMDashboard(tft, captions, host) {};

    void refreshNumbers() {
      getTFT()->setColor(BACKGROUND_COLOR);
      getTFT()->fillRect(IMRect(0, BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT-BAR_HEIGHT));

      getTFT()->print(String(host->getExtAdj()), DATA_FONT_SIZE, MAIN_COLOR, data11);
      getTFT()->print(String(host->getCondMtrAdj()), DATA_FONT_SIZE, MAIN_COLOR, data12);
      getTFT()->print(String(host->getHeatAdj()), DATA_FONT_SIZE, MAIN_COLOR, data13);
      getTFT()->print(host->getSwitchPosString(), DATA_FONT_SIZE, MAIN_COLOR, data21);
      getTFT()->print(String(host->getRefluxRatio(), DATA_PRECISION), DATA_FONT_SIZE, MAIN_COLOR, data22);

      getTFT()->print(getCaptions()->EXT_ADJ_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label11);
      getTFT()->print(getCaptions()->COND_ADJ_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label12);
      getTFT()->print(getCaptions()->HEAT_ADJ_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label13);
      getTFT()->print(getCaptions()->SW_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label21);
      getTFT()->print(getCaptions()->RF_LBL, LBL_FONT_SIZE, MAIN_COLOR_FLAT, label22);
    }

    void draw() {
      getTFT()->paintBackground();
      getTFT()->setColor(MAIN_COLOR);
      getTFT()->fillRect(topBar);
      getTFT()->fillRect(bottomBar);

      getTFT()->print(getCaptions()->DASH3_HDR, HDR_FONT_SIZE, BACKGROUND_COLOR, topBar);
      getTFT()->print(getCaptions()->ARROW_LEFT, HDR_FONT_SIZE, BACKGROUND_COLOR, topLeftRect);

      refreshNumbers();

      getTFT()->print(host->getStateString(), HDR_FONT_SIZE, BACKGROUND_COLOR, bottomBar);
      
      refreshTime = millis();
      refreshRequired = false;
    }

    void handleTouch() {
      /*
      IMPoint touch = getUI()->getTS()->getTouchPosition();

      if (touch.hasValue()) {
        //Serial.println(String(touch.x)+" "+String(touch.y));
        if (topLeftRect.hasPoint(touch)) {

        }
    
      }
      */
    }
    
};

#endif
