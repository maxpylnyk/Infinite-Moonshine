#ifndef IM_PANE_H
#define IM_PANE_H

#include "graphics/IMTFT.h"
#include "graphics/IMRect.h"
#include "utilities/IMCommons.h"
#include "utilities/IMCaptions.h"

class IMTFT;

class IMPane {
  private:
    IMTFT * tft;
    IMCaptions * captions;
/*
  protected:
    unsigned long refreshTime;
    unsigned long refreshTimeout;
    
    IMRect topBar = IMRect(0, SCR_HEIGHT-BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT);
    IMRect bottomBar = IMRect(0, 0, SCR_WIDTH, BAR_HEIGHT);
*/
  public:
    IMPane(IMTFT * tft, IMCaptions * captions) : tft(tft), captions(captions) {};

    virtual void draw() = 0;
    virtual void handleTouch();
    virtual void refresh();
    
    IMTFT * getTFT() {
      return tft;
    }

    IMCaptions * getCaptions() {
      return captions;
    }

};

#endif
