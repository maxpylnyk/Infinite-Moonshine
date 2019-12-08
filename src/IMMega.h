#ifndef IM_MEGA_H
#define IM_MEGA_H

#include "InfiniteMoonshine.h"
#include "graphics/IMTFT.h"
#include "graphics/IMTouchScreen.h"
#include "logic/IMCondenserNode.h"
#include "logic/IMExtractionNode.h"
#include "logic/IMSwitchNode.h"
//#include "utilities/IMLogger.h"
#include "logic/IMValuesHolder.h"

class IMMega : public InfiniteMoonshine {
  private:
    bool blinkVisible;
    uint8_t hh, mm;
    String hours, minutes;
    unsigned long blinkTimeout = 1000;
    unsigned long lastBlinkTime;

    const IMRect fullScr = IMRect(0, 0, SCR_WIDTH, SCR_HEIGHT);
    const IMRect topBar = IMRect(0, TOP_BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT);
    const IMRect bottomBar = IMRect(0, 0, SCR_WIDTH, BAR_HEIGHT);
    const IMRect srcBar = IMRect(0, BAR_HEIGHT, SCR_WIDTH, 2*BAR_HEIGHT);
    const IMRect hoursRect = IMRect(HH_XLO, CLOCK_YLO, HH_XHI, CLOCK_YHI);
    const IMRect minutesRect = IMRect(MM_XLO, CLOCK_YLO, MM_XHI, CLOCK_YHI);
    const IMRect twospotRect = IMRect(TWO_SPOT_XLO, CLOCK_YLO, TWO_SPOT_XHI, CLOCK_YHI);

    const IMRect topLeftRect = IMRect(0, TOP_BAR_HEIGHT, BTN_WIDTH, SCR_HEIGHT);
    const IMRect topL2Rect = IMRect(BTN_WIDTH, TOP_BAR_HEIGHT, 2*BTN_WIDTH, SCR_HEIGHT);
    const IMRect topRightRect = IMRect(SCR_WIDTH-BTN_WIDTH, TOP_BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT);
    const IMRect bottomLeftRect = IMRect(0, 0, BTN_WIDTH, BAR_HEIGHT);
    const IMRect bottomRightRect = IMRect(SCR_WIDTH-BTN_WIDTH, 0, SCR_WIDTH, BAR_HEIGHT);

    const IMRect slot11 = IMRect(0, SCR_HEIGHT/2, DASH_SLOT_WIDTH, TOP_BAR_HEIGHT-1);
    const IMRect slot12 = IMRect(DASH_SLOT_WIDTH, SCR_HEIGHT/2, DASH_SLOT_WIDTH*2, TOP_BAR_HEIGHT-1);
    const IMRect slot13 = IMRect(DASH_SLOT_WIDTH*2, SCR_HEIGHT/2, SCR_WIDTH, TOP_BAR_HEIGHT-1);
    const IMRect slot21 = IMRect(0, BAR_HEIGHT, DASH_SLOT_WIDTH, SCR_HEIGHT/2-1);
    const IMRect slot22 = IMRect(DASH_SLOT_WIDTH, BAR_HEIGHT, DASH_SLOT_WIDTH*2, SCR_HEIGHT/2-1);
    const IMRect slot23 = IMRect(DASH_SLOT_WIDTH*2, BAR_HEIGHT, SCR_WIDTH, SCR_HEIGHT/2-1);

    const IMRect label11 = IMRect(slot11.getXLo(), slot11.getYLo(), slot11.getXHi(), slot11.getYLo()+DASH_LBL_HEIGHT);
    const IMRect label12 = IMRect(slot12.getXLo(), slot12.getYLo(), slot12.getXHi(), slot12.getYLo()+DASH_LBL_HEIGHT);
    const IMRect label13 = IMRect(slot13.getXLo(), slot13.getYLo(), slot13.getXHi(), slot13.getYLo()+DASH_LBL_HEIGHT);
    const IMRect label21 = IMRect(slot21.getXLo(), slot21.getYLo(), slot21.getXHi(), slot21.getYLo()+DASH_LBL_HEIGHT);
    const IMRect label22 = IMRect(slot22.getXLo(), slot22.getYLo(), slot22.getXHi(), slot22.getYLo()+DASH_LBL_HEIGHT);
    const IMRect label23 = IMRect(slot23.getXLo(), slot23.getYLo(), slot23.getXHi(), slot23.getYLo()+DASH_LBL_HEIGHT);

    const IMRect data11 = IMRect(slot11.getXLo(), slot11.getYLo()+DASH_LBL_HEIGHT, slot11.getXHi(), slot11.getYHi()-DASH_LBL_HEIGHT);
    const IMRect data12 = IMRect(slot12.getXLo(), slot12.getYLo()+DASH_LBL_HEIGHT, slot12.getXHi(), slot12.getYHi()-DASH_LBL_HEIGHT);
    const IMRect data13 = IMRect(slot13.getXLo(), slot13.getYLo()+DASH_LBL_HEIGHT, slot13.getXHi(), slot13.getYHi()-DASH_LBL_HEIGHT);
    const IMRect data21 = IMRect(slot21.getXLo(), slot21.getYLo()+DASH_LBL_HEIGHT, slot21.getXHi(), slot21.getYHi()-DASH_LBL_HEIGHT);
    const IMRect data22 = IMRect(slot22.getXLo(), slot22.getYLo()+DASH_LBL_HEIGHT, slot22.getXHi(), slot22.getYHi()-DASH_LBL_HEIGHT);
    const IMRect data23 = IMRect(slot23.getXLo(), slot23.getYLo()+DASH_LBL_HEIGHT, slot23.getXHi(), slot23.getYHi()-DASH_LBL_HEIGHT);

    const IMRect topLabel11 = IMRect(0, DASH_DATA_YHI1, DASH_SLOT_WIDTH, TOP_BAR_HEIGHT-1);
    const IMRect topLabel12 = IMRect(DASH_SLOT_WIDTH, DASH_DATA_YHI1, 2*DASH_SLOT_WIDTH, TOP_BAR_HEIGHT-1);
    const IMRect topLabel13 = IMRect(2*DASH_SLOT_WIDTH, DASH_DATA_YHI1, SCR_WIDTH, TOP_BAR_HEIGHT-1);
    const IMRect topLabel21 = IMRect(0, DASH_DATA_YHI2, DASH_SLOT_WIDTH, SCR_HEIGHT/2);

    const IMRect keyCancel = IMRect(0, 0, KEY_WIDTH, KEY_HEIGHT);
    const IMRect keyOK = IMRect(KEY_WIDTH, 0, 2*KEY_WIDTH, KEY_HEIGHT);
    const IMRect keyClear = IMRect(2*KEY_WIDTH, 0, 3*KEY_WIDTH, KEY_HEIGHT);
    const IMRect key0 = IMRect(3*KEY_WIDTH, 0, 4*KEY_WIDTH, KEY_HEIGHT);
    const IMRect keyBackspace = IMRect(4*KEY_WIDTH, 0, SCR_WIDTH, KEY_HEIGHT);
    const IMRect keyMinus = IMRect(0, KEY_HEIGHT, KEY_WIDTH, 2*KEY_HEIGHT);
    const IMRect keyPlus = IMRect(KEY_WIDTH, KEY_HEIGHT, 2*KEY_WIDTH, 2*KEY_HEIGHT);
    const IMRect key7 = IMRect(2*KEY_WIDTH, KEY_HEIGHT, 3*KEY_WIDTH, 2*KEY_HEIGHT);
    const IMRect key8 = IMRect(3*KEY_WIDTH, KEY_HEIGHT, 4*KEY_WIDTH, 2*KEY_HEIGHT);
    const IMRect key9 = IMRect(4*KEY_WIDTH, KEY_HEIGHT, SCR_WIDTH, 2*KEY_HEIGHT);
    const IMRect key4 = IMRect(2*KEY_WIDTH, 2*KEY_HEIGHT, 3*KEY_WIDTH, 3*KEY_HEIGHT);
    const IMRect key5 = IMRect(3*KEY_WIDTH, 2*KEY_HEIGHT, 4*KEY_WIDTH, 3*KEY_HEIGHT);
    const IMRect key6 = IMRect(4*KEY_WIDTH, 2*KEY_HEIGHT, SCR_WIDTH, 3*KEY_HEIGHT);
    const IMRect key1 = IMRect(2*KEY_WIDTH, 3*KEY_HEIGHT, 3*KEY_WIDTH, SCR_HEIGHT);
    const IMRect key2 = IMRect(3*KEY_WIDTH, 3*KEY_HEIGHT, 4*KEY_WIDTH, SCR_HEIGHT);
    const IMRect key3 = IMRect(4*KEY_WIDTH, 3*KEY_HEIGHT, SCR_WIDTH, SCR_HEIGHT);
    const IMRect keyDisplay = IMRect(0, 2*KEY_HEIGHT, 2*KEY_WIDTH-1, SCR_HEIGHT);
    const IMRect keyLabel = IMRect(keyDisplay.getXLo(), keyDisplay.getYLo(), keyDisplay.getXHi(), keyDisplay.getYLo()+DASH_LBL_HEIGHT*5);
    const IMRect keyData = IMRect(keyDisplay.getXLo(), keyDisplay.getYLo()+KEY_HEIGHT/2, keyDisplay.getXHi(), keyDisplay.getYHi());

    Language locale = Language::RUSSIAN;
    IMCaptions captions = IMCaptions(locale);

    Panes activePane;
    Panes prevActivePane;

    bool changed;
    bool appendAllowed;
    uint8_t errCount;
    uint32_t editValue;
    String editLabel;
    IMErrors displayedErrors;
    String errText;
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
    void printErrors();
    bool handleErrors();
    void moveMotors();

    void applyEditing();
    void handleTouch();
    void drawBottomBar();
    void drawPrevPane();
    bool drawConfirmDialog();
    void drawSlot(String, String, IMRect);
    void drawInitPane();
    void drawFrontPane();
    void drawErrorsPane();
    void drawDash1Data();
    void drawDash1();
    void drawDash2Data();
    void drawDash2();
    void drawDash3Data();
    void drawDash3();
    void drawKeyboardData();
    void drawKeyboard(int, String);
    void update();
    void blink();
    void drawMM();
    void drawHH();
    
    void readPrevLog();
    void logRestart();
    void logRestart(Board);
    void logStateChange();
    void logData();

    void printDebugText();
    
  public:
    IMMega();

    bool init();
    void loop();
    void debug();
    void receiveCallsign();

};

#endif
