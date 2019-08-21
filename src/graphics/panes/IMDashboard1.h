#ifndef IM_DASHBOARD_1_H
#define IM_DASHBOARD_1_H

#include "IMDashboard.h"

class IMDashboard1 : public IMDashboard {
  public:
    IMDashboard1(IMTFT*, IMCaptions*, IMValuesHolder*);

    void draw();
    void handleTouch();
    void refresh();
    
};

#endif
