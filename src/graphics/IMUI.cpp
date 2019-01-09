#include "IMUI.h"

IMUI::IMUI() {}

bool IMUI::init() {
  bool result = tft.init();
  result &= ts.init();
  currentPane->draw();
  return result;
}

void IMUI::handleTouch() {
  IMPoint touch = ts.getTouchPosition();

  if (touch.hasValue()) {
    

    Serial.println(String(touch.x)+" "+String(touch.y));
    /*
    int buttonWidth = tft.width() * BUTTONS_WIDTH_MULTIPLIER;
    int infoXStart = tft.width() - buttonWidth;
    int cancelXEnd = buttonWidth;
    int topYStart = tft.height() - buttonWidth;
    int barYEnd = tft.height() * BAR_HEIGHT_MULTIPLIER;

    if (touch.y < barYEnd) {
      bottomBarPressed();
    } else if (touch.y > topYStart) {
      if (touch.x < cancelXEnd) {
        cancelPressed();
      } else if (touch.x > infoXStart) {
        infoPressed();
      }
    }*/
  }
}

IMTFT * IMUI::getTFT() {
  return &tft;
}
