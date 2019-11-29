#ifndef IM_FRONT_PANE_H
#define IM_FRONT_PANE_H

#include "IMPane.h"
#include "utilities/IMTimer.h"

class IMFrontPane : public IMPane {
  private:
    IMTimer * timer;

    IMRect srcBar = IMRect(0, BAR_HEIGHT, SCR_WIDTH, 2*BAR_HEIGHT);
    IMRect timeRect = IMRect(0, 2*BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT-BAR_HEIGHT);


  public:
    IMFrontPane(IMTFT * tft, IMCaptions * captions, IMTimer * timer) : 
      IMPane(tft, captions, FRONT_PANE_TIMEOUT), timer(timer) {};

    void draw() {
      getTFT()->paintBackground();
      getTFT()->setColor(MAIN_COLOR);
      getTFT()->fillRect(topBar);
      getTFT()->fillRect(bottomBar);

      getTFT()->printNum(timer->getTime(), timeRect);
      getTFT()->print("Тип сырья объём", 2, MAIN_COLOR, srcBar);
      getTFT()->print("СТАТУС", HDR_FONT_SIZE, BACKGROUND_COLOR, bottomBar);
      
      refreshTime = millis();
      refreshRequired = false;
    }

    void handleTouch() {

    }

    void refresh() {
      if (millis() - refreshTime >= refreshTimeout || refreshRequired) {
        draw();
      }
    }

};

#endif
