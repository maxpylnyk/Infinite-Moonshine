#ifndef IM_MEGA_H
#define IM_MEGA_H

#include "InfiniteMoonshine.h"
#include "graphics/IMTFT.h"
#include "graphics/IMTouchScreen.h"
#include "logic/IMCondenserNode.h"
#include "logic/IMExtractionNode.h"
#include "logic/IMSwitchNode.h"
//#include "utilities/IMLogger.h"
#include "utilities/IMValuesHolder.h"

class IMMega : public InfiniteMoonshine {
  private:
    bool blinkVisible;
    bool refreshRequired;    
    unsigned long refreshTime;
    unsigned long refreshTimeout;
    unsigned long blinkTimeout = 1000;
    unsigned long lastBlinkTime;
    IMRect blinkRect = IMRect(0, 115, 10, 125);

    const IMRect fullScr = IMRect(0, 0, SCR_WIDTH, SCR_HEIGHT);
    const IMRect topBar = IMRect(0, SCR_HEIGHT-BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT);
    const IMRect bottomBar = IMRect(0, 0, SCR_WIDTH, BAR_HEIGHT);
    const IMRect srcBar = IMRect(0, BAR_HEIGHT, SCR_WIDTH, 2*BAR_HEIGHT);
    const IMRect timeRect = IMRect(0, 2*BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT-BAR_HEIGHT);

    const IMRect topLeftRect = IMRect(0, SCR_HEIGHT-BAR_HEIGHT, BTN_WIDTH, SCR_HEIGHT);
    const IMRect topL2Rect = IMRect(BTN_WIDTH, SCR_HEIGHT-BAR_HEIGHT, 2*BTN_WIDTH, SCR_HEIGHT);
    const IMRect topRightRect = IMRect(SCR_WIDTH-BTN_WIDTH, SCR_HEIGHT-BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT);
    const IMRect bottomLeftRect = IMRect(0, 0, BTN_WIDTH, BAR_HEIGHT);
    const IMRect bottomRightRect = IMRect(SCR_WIDTH-BTN_WIDTH, 0, SCR_WIDTH, BAR_HEIGHT);

    const IMRect slot11 = IMRect(0, SCR_HEIGHT/2, DASH_SLOT_WIDTH, SCR_HEIGHT-BAR_HEIGHT);
    const IMRect slot12 = IMRect(DASH_SLOT_WIDTH, SCR_HEIGHT/2, DASH_SLOT_WIDTH*2, SCR_HEIGHT-BAR_HEIGHT);
    const IMRect slot13 = IMRect(DASH_SLOT_WIDTH*2, SCR_HEIGHT/2, SCR_WIDTH, SCR_HEIGHT-BAR_HEIGHT);
    const IMRect slot21 = IMRect(0, BAR_HEIGHT, DASH_SLOT_WIDTH, SCR_HEIGHT/2);
    const IMRect slot22 = IMRect(DASH_SLOT_WIDTH, BAR_HEIGHT, DASH_SLOT_WIDTH*2, SCR_HEIGHT/2);
    const IMRect slot23 = IMRect(DASH_SLOT_WIDTH*2, BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT/2);

    const IMRect label11 = IMRect(slot11.getXLo(), slot11.getYLo(), slot11.getXHi(), slot11.getYLo()+DASH_LBL_HEIGHT*5);
    const IMRect label12 = IMRect(slot12.getXLo(), slot12.getYLo(), slot12.getXHi(), slot12.getYLo()+DASH_LBL_HEIGHT*5);
    const IMRect label13 = IMRect(slot13.getXLo(), slot13.getYLo(), slot13.getXHi(), slot13.getYLo()+DASH_LBL_HEIGHT*5);
    const IMRect label21 = IMRect(slot21.getXLo(), slot21.getYLo(), slot21.getXHi(), slot21.getYLo()+DASH_LBL_HEIGHT*5);
    const IMRect label22 = IMRect(slot22.getXLo(), slot22.getYLo(), slot22.getXHi(), slot22.getYLo()+DASH_LBL_HEIGHT*5);
    const IMRect label23 = IMRect(slot23.getXLo(), slot23.getYLo(), slot23.getXHi(), slot23.getYLo()+DASH_LBL_HEIGHT*5);

    const IMRect data11 = IMRect(slot11.getXLo(), slot11.getYLo()+DASH_LBL_HEIGHT, slot11.getXHi(), slot11.getYHi());
    const IMRect data12 = IMRect(slot12.getXLo(), slot12.getYLo()+DASH_LBL_HEIGHT, slot12.getXHi(), slot12.getYHi());
    const IMRect data13 = IMRect(slot13.getXLo(), slot13.getYLo()+DASH_LBL_HEIGHT, slot13.getXHi(), slot13.getYHi());
    const IMRect data21 = IMRect(slot21.getXLo(), slot21.getYLo()+DASH_LBL_HEIGHT, slot21.getXHi(), slot21.getYHi());
    const IMRect data22 = IMRect(slot22.getXLo(), slot22.getYLo()+DASH_LBL_HEIGHT, slot22.getXHi(), slot22.getYHi());
    const IMRect data23 = IMRect(slot23.getXLo(), slot23.getYLo()+DASH_LBL_HEIGHT, slot23.getXHi(), slot23.getYHi());

    Language locale = Language::RUSSIAN;
    IMCaptions captions = IMCaptions(locale);
    State currentState = STAND_BY_STATE;

    Panes activePane;
    Panes prevActivePane;

    IMTouchScreen ts;
    IMTFT tft = IMTFT(locale);

    IMBarometer bar = IMBarometer();
    IMHydroLevel hlvl = IMHydroLevel();
    IMAlcoholSensor alc = IMAlcoholSensor();
    IMThermometers trm = IMThermometers();

    IMHeater heater = IMHeater();
    IMStepMotor outMtr = IMStepMotor(MTR1_1_PIN, MTR1_2_PIN, MTR1_3_PIN, MTR1_4_PIN);
    IMStepMotor retMtr = IMStepMotor(MTR2_1_PIN, MTR2_2_PIN, MTR2_3_PIN, MTR2_4_PIN);
    IMStepMotor condMtr = IMStepMotor(MTR3_1_PIN, MTR3_2_PIN, MTR3_3_PIN, MTR3_4_PIN);
    IMStepMotor swMtr = IMStepMotor(MTR4_1_PIN, MTR4_2_PIN, MTR4_3_PIN, MTR4_4_PIN);

    IMCondenserNode condNode = IMCondenserNode(&trm, &condMtr);
    IMExtractionNode extNode = IMExtractionNode(&hlvl, &bar, &trm, &heater, &outMtr, &retMtr);
    IMSwitchNode swNode = IMSwitchNode(&alc, &swMtr);
    IMValuesHolder host = IMValuesHolder(&condNode, &extNode, &swNode, &trm);
    
    //IMLogger log = IMLogger();

    void setMasterSPI();
    bool initUI();
    void sendData();
    void receiveData();
    void showErrors();
    bool handleErrors();
    void moveMotors();

    void handleTouch();
    void drawBottomBar();
    void drawInitPane();
    void drawFrontPane();
    void drawErrorsPane();
    void drawDash1Data();
    void drawDash1();
    void drawDash2Data();
    void drawDash2();
    void drawDash3Data();
    void drawDash3();
    void drawKeyboardData(int);
    void drawKeyboard(int);
    bool refresh();
    bool refresh(bool);
    void requireRefresh();
    void blink();

    bool sessionIsActive();
    bool setState(State);

  public:
    IMMega();

    bool init();
    void loop();
    void debug();
    void receiveCallsign();

};

#endif
