#ifndef IM_INIT_PANE_H
#define IN_INIT_PANE_H

#include "IMPane.h"

class IMInitPane : public IMPane {
  public:
    IMInitPane(IMTFT * tft, IMCaptions * captions) : IMPane(tft, captions) {}

    void draw() {
        IMRect r = IMRect(0, 0, SCR_WIDTH, SCR_HEIGHT);
        getTFT()->paintBackground();
        getTFT()->print(getCaptions()->STARTING, PLAIN_FONT_SIZE, MAIN_COLOR, r);
    }

    void handleTouch() {}
    void refresh() {}
};

#endif
