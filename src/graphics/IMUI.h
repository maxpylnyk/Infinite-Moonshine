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
class IMInitPane;

class IMUI {
  private:
    Panes activePane;
    Language locale;
    IMCaptions * captions;
    IMTimer * timer;
    IMValuesHolder * host;

    IMTouchScreen ts;
    IMTFT tft = IMTFT(locale);

    IMInitPane initPane = IMInitPane(&tft, captions);
    IMFrontPane frontPane = IMFrontPane(&tft, captions, timer);
    IMErrorsPane errorsPane = IMErrorsPane(&tft, captions);

    void initPanes();

  public:
    IMUI(Language, IMCaptions*, IMTimer*, IMValuesHolder*);

    bool init();
    void handleTouch();
    IMTFT * getTFT();

    void drawFrontPane();
    void drawErrorsPane(IMErrors*);

    void refresh();
    void requireRefresh();

};

#endif
