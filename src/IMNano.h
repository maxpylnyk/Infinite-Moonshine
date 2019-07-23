#ifndef IM_NANO_H
#define IM_NANO_H

#include "InfiniteMoonshine.h"
#include "utilities/IMTimer.h"
#include "utilities/IMLogger.h"
#include "sensors/IMBarometer.h"
#include "graphics/IMUI.h"

class IMNano : public InfiniteMoonshine { //manual pause only
  private:
    bool resumePrevSession = false;

    uint8_t hydroLevel;
    uint8_t heatPower;      //ctrl
    uint8_t heatAdjStep;    //ctrl set 0 for no adj (debug and manual modes)
    uint8_t refluxRatio;    //ctrl
    uint16_t alcLevel;
    int16_t condMtrAdj;
    int16_t extMtrAdj;  //ctrl
    int32_t outMtrPos;  //ctrl
    int32_t retMtrPos;  //ctrl
    int32_t condMtrPos;
    uint32_t switchPosition; //ctrl debug and manul modes
    
    float steamTemp;
    float condTemp;
    float pipeTemp;
    float envTemp; //from BAR or RTC?
    float pressure;

    IMLogger logger = IMLogger();
    IMBarometer bar = IMBarometer();

    void readPrevLog();
    void logRestart();
    void logRestart(Board);
    void logStateChange();
    void logData();
    void sendData();
    void receiveData();

  public:
    IMNano();

    bool init();
    void loop();
    void debug();
    void receiveCallsign();
    
};

#endif
