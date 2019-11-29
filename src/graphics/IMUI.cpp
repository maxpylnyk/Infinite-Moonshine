#include "IMUI.h"

IMUI::IMUI(Language locale, IMCaptions * captions, IMTimer * timer,
  IMValuesHolder * host) : locale(locale), captions(captions), 
  timer(timer), host(host) {}

bool IMUI::init() {
  bool result = tft.init();
  result &= ts.init();

  errorsPane.setUI(this);
  frontPane.setUI(this);
  dash1.setUI(this);
  dash2.setUI(this);
  dash3.setUI(this);

  initPane.draw();
  activePane = Panes::INIT;
  prevActivePane = activePane;
  return result;
}

void IMUI::handleTouch() {
  switch(activePane) {
    case FRONT:
      frontPane.handleTouch();
      break;
    case DASH1:
      dash1.handleTouch();
      break;
    case DASH2:
      dash2.handleTouch();
      break;
    case DASH3:
      dash3.handleTouch();
      break;
  }
}

IMTFT * IMUI::getTFT() {
  return &tft;
}

IMTouchScreen * IMUI::getTS() {
  return &ts;
}

void IMUI::refresh() {
  switch(activePane) {
    case FRONT:
      frontPane.refresh();
      prevActivePane = FRONT;
      break;
    case DASH1:
      if (dash1.refresh(prevActivePane != DASH1)) {
        prevActivePane = DASH1;
      }
      break;
    case DASH2:
      if (dash2.refresh(prevActivePane != DASH2)) {
        prevActivePane = DASH2;
      }
      break;
    case DASH3:
      if (dash3.refresh(prevActivePane != DASH3)) {
        prevActivePane = DASH3;
      }
      break;
    case ERROR:
      errorsPane.draw();
      prevActivePane = ERROR;
  }
}

void IMUI::requireRefresh() {
  switch(activePane) {
    case FRONT:
      frontPane.requireRefresh();
      break;
    case DASH1:
      dash1.requireRefresh();
      break;
    case DASH2:
      dash2.requireRefresh();
      break;
    case DASH3:
      dash3.requireRefresh();
      break;
  }
}

void IMUI::drawFrontPane() {
  frontPane.draw();
  activePane = Panes::FRONT;
}

void IMUI::drawErrorsPane(IMErrors * list) {
  errorsPane.draw();
  errorsPane.setErrors(list);
  activePane = Panes::ERROR;
}

void IMUI::drawDash1() {
  activePane = Panes::DASH1;
  refresh();
}

void IMUI::drawDash2() {
  activePane = Panes::DASH2;
  refresh();
}

void IMUI::drawDash3() {
  activePane = Panes::DASH3;
  refresh();
}

void IMUI::blink() {
  if (millis() - lastBlinkTime < blinkTimeout) {
    return;
  }

  if (blinkVisible) {
    tft.setColor(MAIN_COLOR);
  } else {
    tft.setColor(BACKGROUND_COLOR);
  }
  tft.fillRect(blinkRect);
  blinkVisible = !blinkVisible;
  lastBlinkTime = millis();
}
