#ifndef IM_UNO_H
#define IM_UNO_H

#include "InfiniteMoonshine.h"
#include "utilities/IMTimer.h"
#include "utilities/IMLogger.h"
#include "sensors/IMBarometer.h"
#include "graphics/IMUI.h"
#include <SPI.h>

#define noop ((void) 0)
#define wait noop noop noop noop noop noop noop noop noop noop noop 

class IMUno : public InfiniteMoonshine {
  private:
    static const uint8_t SS_PIN = 4;
    static const uint8_t RST_PIN = A5;

    StateIndex currentState;
    SPISettings settings = SPISettings(4000000, MSBFIRST, SPI_MODE0);

    void initMasterSPI();
    void beginTransfer();
    uint8_t transferByte(uint8_t);
    void endTransfer();

    bool checkSlave();
    void transferData();
    void restartSlave();
  
  protected:
    bool readCallsign(uint8_t);
    uint8_t getCallsign();

  public:
    IMUno();

    bool init();
    void loop();
    void debug();
    
};

#endif
