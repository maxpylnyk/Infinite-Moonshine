#ifndef IM_DASHBOARD_H
#define IM_DASHBOARD_H

#include "IMPane.h"

class IMDashboard : public IMPane {
  protected:
    const IMRect slot11 = IMRect(0, SCR_HEIGHT/2, DASH_SLOT_WIDTH, SCR_HEIGHT-BAR_HEIGHT);
    const IMRect slot12 = IMRect(DASH_SLOT_WIDTH, SCR_HEIGHT/2, DASH_SLOT_WIDTH*2, SCR_HEIGHT-BAR_HEIGHT);
    const IMRect slot13 = IMRect(DASH_SLOT_WIDTH*2, SCR_HEIGHT/2, SCR_WIDTH, SCR_HEIGHT-BAR_HEIGHT);
    const IMRect slot21 = IMRect(0, BAR_HEIGHT, DASH_SLOT_WIDTH, SCR_HEIGHT/2);
    const IMRect slot22 = IMRect(DASH_SLOT_WIDTH, BAR_HEIGHT, DASH_SLOT_WIDTH*2, SCR_HEIGHT/2);
    const IMRect slot23 = IMRect(DASH_SLOT_WIDTH*2, BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT/2);

    const IMRect label11 = IMRect(slot11.getXLo(), slot11.getYLo(), slot11.getXHi(), slot11.getYLo()+DASH_LBL_HEIGHT);
    const IMRect label12 = IMRect(slot12.getXLo(), slot12.getYLo(), slot12.getXHi(), slot12.getYLo()+DASH_LBL_HEIGHT);
    const IMRect label13 = IMRect(slot13.getXLo(), slot13.getYLo(), slot13.getXHi(), slot13.getYLo()+DASH_LBL_HEIGHT);
    const IMRect label21 = IMRect(slot21.getXLo(), slot21.getYLo(), slot21.getXHi(), slot21.getYLo()+DASH_LBL_HEIGHT);
    const IMRect label22 = IMRect(slot22.getXLo(), slot22.getYLo(), slot22.getXHi(), slot22.getYLo()+DASH_LBL_HEIGHT);
    const IMRect label23 = IMRect(slot23.getXLo(), slot23.getYLo(), slot23.getXHi(), slot23.getYLo()+DASH_LBL_HEIGHT);

    const IMRect data11 = IMRect(slot11.getXLo(), slot11.getYLo()+DASH_LBL_HEIGHT, slot11.getXHi(), slot11.getYHi());
    const IMRect data12 = IMRect(slot12.getXLo(), slot12.getYLo()+DASH_LBL_HEIGHT, slot12.getXHi(), slot12.getYHi());
    const IMRect data13 = IMRect(slot13.getXLo(), slot13.getYLo()+DASH_LBL_HEIGHT, slot13.getXHi(), slot13.getYHi());
    const IMRect data21 = IMRect(slot21.getXLo(), slot21.getYLo()+DASH_LBL_HEIGHT, slot21.getXHi(), slot21.getYHi());
    const IMRect data22 = IMRect(slot22.getXLo(), slot22.getYLo()+DASH_LBL_HEIGHT, slot22.getXHi(), slot22.getYHi());
    const IMRect data23 = IMRect(slot23.getXLo(), slot23.getYLo()+DASH_LBL_HEIGHT, slot23.getXHi(), slot23.getYHi());

  public:
    IMDashboard(IMTFT * tft, IMCaptions * captions) : IMPane(tft, captions) {}

    virtual void draw() = 0;
    virtual void handleTouch();
    virtual void refresh();

};

#endif
