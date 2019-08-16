#include "IMUI.h"

IMUI::IMUI(Language locale, IMCaptions * captions, IMTimer * timer) : 
  locale(locale), captions(captions), timer(timer) {}

bool IMUI::init() {
  bool result = tft.init();
  result &= ts.init();
  initPanes();
  initPane.draw();
  activePane = Panes::INIT;
  return result;
}

void IMUI::initPanes() {

}

void IMUI::handleTouch() {
  IMPoint touch = ts.getTouchPosition();

  if (touch.hasValue()) {
    //Serial.println(String(touch.x)+" "+String(touch.y));

    switch(activePane) {
      case FRONT:
        frontPane.handleTouch();
        break;
    }
  }
}

IMTFT * IMUI::getTFT() {
  return &tft;
}

void IMUI::refresh() {
  switch(activePane) {
    case FRONT:
      frontPane.refresh();
      break;
  }
}

void IMUI::drawFrontPane() {
  frontPane.draw();
  activePane = Panes::FRONT;
}

void IMUI::drawErrorsPane(IMErrors * list) {
  errorsPane.setErrors(list);
  errorsPane.draw();
  activePane = Panes::ERROR;
}
