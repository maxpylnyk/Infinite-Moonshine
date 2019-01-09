#ifndef IM_INFO_BUTTON_H
#define IM_INFO_BUTTON_H

#include "graphics/IMButton.h"

class IMInfoButton : public IMButton {
  private:
    static const int radius = 15;
    static const int lineHeight = 8;
  public:
    IMInfoButton(IMPane * owner, IMRect place, uint16_t color);

    void draw();
    void action();
    
};

#endif
