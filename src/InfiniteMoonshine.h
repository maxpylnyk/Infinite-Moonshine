#ifndef INFINITE_MOONSHINE_H
#define INFINITE_MOONSHINE_H

#include "Arduino.h"
#include <avr/wdt.h>
#include "stdint.h"
#include "logic/IMStates.h"
#include "utilities/IMTimer.h"
#include "utilities/IMErrors.h"
#include "utilities/IMCommons.h"
#include "utilities/IMCaptions.h"
//#include "control/IMHeater.h"
//#include "sensors/IMHydroLevel.h"
//#include "sensors/IMAlcoholSensor.h"
//#include "sensors/IMThermometers.h"
//#include "control/IMStepMotor.h"

#define DEBUG_MODE                1
#define MANUAL_MODE               0
#define UNSTABLE_PRESSURE_REGION  0

#define VERSION                   "beta"

class InfiniteMoonshine {
  protected:
    static const char onlineSign        = '*';
    static const char initSign          = 'i';
    static const char restartSign       = 'r';
    static const char dataSign          = '>';
    static const byte endOfTransmission = 64;

    static const uint8_t rstWdtDelay = WDTO_8S;

    static const byte rstPinDelay = 10;
    static const byte attemptsLimit = 3;
    static const byte responseTimeLimit = 10;//measure that
    static const byte bufferSize = 64;

    static const long maxSpeed = 8 * 250000;
    static const long usbSpeed = 9600;
    static const long serialSpeed = maxSpeed;
    static const unsigned long bytesArrivalTime = (8 * bufferSize * 1000000) / serialSpeed;
    static const unsigned long watchdogTimeout = 7 * 1000;
    static const unsigned long callsignTimeout = 1 * 1000;//measure
    static const unsigned long dataSyncTimeout = 2 * 1000;//measure
    static const unsigned long logTimeout = 20 * 1000;//measure
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
    uint8_t pause = Pause::RESUME;
    uint8_t manualPause = Pause::RESUME;

    byte connectionAttempts = 0;
    char callsign = initSign;
    uint8_t stateIndex = 0;
    int rstPin;
    uint32_t sessionName = 0;
    unsigned long responseTime = 0;
    //add timers

    IMTimer timer = IMTimer();
    IMErrors errors = IMErrors();
    String queue = "";
    HardwareSerial * port;
    HardwareSerial * debugPort;

    uint8_t isPaused();
    void setPause(uint8_t);
    void setManualPause(uint8_t);

    uint8_t getStateIndex();
    void setStateIndex(uint8_t);

    uint32_t getSessionName();
    void setSessionName(uint32_t);
    
    void initWatchdog();
    void restartWatchdog();
    
    void restartOther();

    void sendCallsign();
    void sendData();
    void receiveData();
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
