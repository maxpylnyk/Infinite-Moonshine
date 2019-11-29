#ifndef IM_UI_H
#define IM_UI_H

#include "graphics/IMTFT.h"
#include "graphics/IMTouchScreen.h"
#include "graphics/panes/IMPanes.h"
#include "graphics/buttons/IMButtons.h"
#include "utilities/IMCaptions.h"
#include "utilities/IMTimer.h"
#include "utilities/IMValuesHolder.h"

class IMPane;

class IMUI {
  private:
    bool blinkVisible;
    unsigned long blinkTimeout = 1000;
    unsigned long lastBlinkTime;
    IMRect blinkRect = IMRect(0, 115, 10, 125);

    Panes activePane;
    Panes prevActivePane;
    Language locale;
    IMCaptions * captions;
    IMTimer * timer;
    IMValuesHolder * host;

    IMTouchScreen ts;
    IMTFT tft = IMTFT(locale);

    IMInitPane initPane = IMInitPane(&tft, captions);
    IMFrontPane frontPane = IMFrontPane(&tft, captions, timer);
    IMErrorsPane errorsPane = IMErrorsPane(&tft, captions);
    IMDashboard1 dash1 = IMDashboard1(&tft, captions, host);
    IMDashboard2 dash2 = IMDashboard2(&tft, captions, host);
    IMDashboard3 dash3 = IMDashboard3(&tft, captions, host);

  public:
    IMUI(Language, IMCaptions*, IMTimer*, IMValuesHolder*);

    bool init();
    void handleTouch();
    IMTFT * getTFT();
    IMTouchScreen * getTS();

    void drawFrontPane();
    void drawErrorsPane(IMErrors*);
    void drawDash1();
    void drawDash2();
    void drawDash3();

    void refresh();
    void requireRefresh();

    void blink();

};

#endif
