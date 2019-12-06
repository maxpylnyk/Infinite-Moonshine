#ifndef INFINITE_MOONSHINE_H
#define INFINITE_MOONSHINE_H

#include <avr/wdt.h>
#include "utilities/IMTimer.h"
#include "utilities/IMErrors.h"
#include "utilities/IMCommons.h"
#include "utilities/IMCaptions.h"
#include "logic/IMSession.h"

class InfiniteMoonshine {
  protected:
    static const char onlineSign        = '*';
    static const char initSign          = 'i';
    static const char restartSign       = 'r';
    static const char dataSign          = '>';
    static const byte endOfTransmission = 64;

    static const uint8_t rstWdtDelay = WDTO_8S;

    static const byte rstPinDelay = 10;
    static const byte attemptsLimit = 1;
    static const byte bufferSize = 64;
    static const uint16_t blinkDelay = 420;

    static const long maxSpeed = 8 * 250000;
    static const long usbSpeed = 9600;
    static const long serialSpeed = maxSpeed;
    static const unsigned long bytesArrivalTime = (8 * bufferSize * 1000000) / serialSpeed;
    static const unsigned long watchdogTimeout = 7 * 1000;
    static const unsigned long responseTimeLimit = 5 * 1000;
    static const unsigned long callsignTimeout = 10 * 1000;
    static const unsigned long megaInitDelay = 5 * 1000 +
#if DISABLE_ALC_METER
    0;
#else
    60 * 1000;
#endif
    static const unsigned long controlPauseTimeout = 10 * 60 * 1000;//measure
    static const unsigned long controlTimeout =
#if UNSTABLE_PRESSURE_REGION
    1
#else
    6 
#endif
    * 60 * 60 * 1000;

    bool initialize = true;
    bool thisRestarted = false;
    bool otherRestarted = false;
    bool callsignReceived = true;
    bool transfering = false;
    uint8_t pause = Pause::RESUME;
    uint8_t manualPause = Pause::RESUME;

    byte connectionAttempts = 0;
    byte restartAttempts = 0;
    char callsign = initSign;
    int rstPin;
    //unsigned long callsignTime;
    unsigned long responseTime;
    unsigned long wtdRstTime;

    IMTimer timer = IMTimer();
    IMTimer waitingTimer = IMTimer();
    IMErrors errors = IMErrors();
    String queue = "";
    HardwareSerial * port;
    HardwareSerial * debugPort;
    IMSession session;
    String debugText;

    uint8_t isPaused();
    void setPause(uint8_t);
    void setManualPause(uint8_t);
    
    void initWatchdog();
    void disableWatchdog();
    void restartWatchdog();
    
    void restartOther();

    void sendCallsign();
    virtual void sendData() = 0;
    void addToQueue(byte number, String value);
    void endQueue();

    float calculateTemp(float pressure);

  public:
    InfiniteMoonshine(int rstPin);

    bool init();
    void loop();
    void debug();
    void receiveCallsign();

};

#endif
