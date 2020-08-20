#ifndef IM_MEGA_H
#define IM_MEGA_H

#include <avr/wdt.h>
#include "other/IMTimer.h"
#include "other/IMErrors.h"
#include "other/IMConstants.h"
#include "elements/IMSavedValues.h"
#include "elements/IMHardwareInterface.h"

class IMMega {
  private:
    static const char onlineSign        = '*';
    static const char confirmSign       = '@';
    static const char initSign          = 'i';
    static const char restartSign       = 'r';
    static const char dataSign          = '>';
    static const char endOfTransmission = '<';

    static const byte bufferSize = 64;

    static const long maxSpeed = 8 * 250000;
    static const long usbSpeed = 9600;
    static const long serialSpeed = 115000;
    static const unsigned long bytesArrivalTime = (8 * bufferSize * 1000000) / serialSpeed;
    static const unsigned long blinkTimeout = 420;

    bool initialize = true;
    bool transfering = false;
    bool expectingConfirm = false;
    bool errorsPrinted = false;
    bool blinkVisible = false;
    char callsign = initSign;
    unsigned long lastBlinkTime = 0;

    IMTimer timer = IMTimer();
    IMErrors errors = IMErrors();
    String queue = "";
    String debugText;
    HardwareSerial * port;
    HardwareSerial * debugPort;
    IMSavedValues savedValues;

    IMBarometer bar = IMBarometer();
    IMHydroLevel hlvl = IMHydroLevel();
    IMAlcoholSensor alc = IMAlcoholSensor();
    IMThermometers trm = IMThermometers();

    IMHeater heater = IMHeater();
    IMStepMotor outMtr = IMStepMotor(MTR1_1_PIN, MTR1_2_PIN, MTR1_3_PIN, MTR1_4_PIN);
    IMStepMotor retMtr = IMStepMotor(MTR2_1_PIN, MTR2_2_PIN, MTR2_3_PIN, MTR2_4_PIN);
    IMStepMotor condMtr = IMStepMotor(MTR3_1_PIN, MTR3_2_PIN, MTR3_3_PIN, MTR3_4_PIN);
    IMStepMotor swMtr = IMStepMotor(MTR4_1_PIN, MTR4_2_PIN, MTR4_3_PIN, MTR4_4_PIN);

    IMHardwareInterface host = IMHardwareInterface(&hlvl, &alc, &trm, &bar, &heater, &outMtr, &retMtr, &condMtr, &swMtr);

    void addToQueue(uint8_t number, String value);
    void endQueue();

    void sendData();
    void receiveData();
    bool movingMotors();
    void updateValues();
    void sendErrors();
    void blink();
    
  public:
    IMMega();

    bool init();
    void loop();
    void sendCallsign();
    void receiveCallsign();

};

#endif
