#ifndef IM_PANE_H
#define IM_PANE_H

#include "graphics/IMTFT.h"
#include "graphics/IMUI.h"
#include "graphics/IMRect.h"
#include "utilities/IMCommons.h"
#include "utilities/IMCaptions.h"

const IMRect topBar = IMRect(0, SCR_HEIGHT-BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT);
const IMRect bottomBar = IMRect(0, 0, SCR_WIDTH, BAR_HEIGHT);

const IMRect topLeftRect = IMRect(0, SCR_HEIGHT-BAR_HEIGHT, BTN_WIDTH, SCR_HEIGHT);
const IMRect topRightRect = IMRect(SCR_WIDTH-BTN_WIDTH, SCR_HEIGHT-BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT);

class IMTFT;
class IMUI;

class IMPane {
  private:
    IMTFT * tft;
    IMUI * ui;
    IMCaptions * captions;

  protected:
    bool refreshRequired;    
    unsigned long refreshTime;
    unsigned long refreshTimeout;

  public:
    IMPane(IMTFT * tft, IMCaptions * captions, unsigned long refreshTimeout) 
      : tft(tft), captions(captions), refreshTimeout(refreshTimeout) {};

    virtual void draw() = 0;
    virtual void handleTouch();
    virtual void refresh();
    
    IMTFT * getTFT() {
      return tft;
    }

    IMCaptions * getCaptions() {
      return captions;
    }

    void requireRefresh() {
      refreshRequired = true;
    }

    void setUI(IMUI * owner) {
      ui = owner;
    }

    IMUI * getUI() {
      return ui;
    }

};

#endif
