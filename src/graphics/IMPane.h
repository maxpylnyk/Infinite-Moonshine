#ifndef IM_PANE_H
#define IM_PANE_H

#include "graphics/IMUI.h"

class IMUI;

class IMPane {
  private:
    IMUI * ui;

  public:
    IMPane(IMUI * ui) : ui(ui) {};

    virtual void draw();
    
    IMUI * getUI() {
      return ui;
    }

};

#endif
