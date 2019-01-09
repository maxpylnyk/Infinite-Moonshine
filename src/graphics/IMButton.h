#ifndef IM_BUTTON_H
#define IM_BUTTON_H

#include "graphics/IMUI.h"
#include "graphics/IMRect.h"

class IMUI;
class IMTFT;
class IMPane;

class IMButton {
  protected:
    uint16_t color;
    IMUI * ui;
    IMTFT * tft;
    IMPane * owner;
    IMRect place;

  public:
    IMButton(IMPane * owner, IMRect place, uint16_t color) 
      : owner(owner), place(place), color(color) {
        ui = owner->getUI();
        tft = ui->getTFT();
      }

    virtual void draw() = 0;
    virtual void action();

    void erase() {
      tft->setColor(IMUI::BACKGROUND_COLOR);
      tft->fillRect(place);
    }
    
    bool hasPoint(IMPoint p) {
      return place.hasPoint(p);
    }

};

#endif
