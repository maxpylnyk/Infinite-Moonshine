#ifndef IM_BUTTON_H
#define IM_BUTTON_H

#include "graphics/IMRect.h"
#include "graphics/IMTFT.h"
#include "graphics/panes/IMPane.h"
#include "utilities/IMCommons.h"

//class IMTFT;
//class IMPane;

#define BUTTON_WIDTH 50

class IMButton {
  protected:
    IMRect * place;

  public:
    IMButton(IMRect * place) 
      : place(place) {}

    virtual void draw() = 0;
    virtual void action();
    
    bool hasPoint(IMPoint p) {
      return place->hasPoint(p);
    }

};

#endif
