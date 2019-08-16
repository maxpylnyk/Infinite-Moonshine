#include "graphics/IMTouchScreen.h"

IMTouchScreen::IMTouchScreen() {}

bool IMTouchScreen::init() {
  return true;
}

static void insert_sort(int array[], uint8_t size) {
    uint8_t j;
    int save;

    for (int i = 1; i < size; i++) {
        save = array[i];
        for (j = i; j >= 1 && save < array[j - 1]; j--)
            array[j] = array[j - 1];
        array[j] = save;
    }
}

IMPoint IMTouchScreen::getPoint(void) {
    int x, y, z;
    int samples[NUMSAMPLES];
    uint8_t i, valid;

    valid = 1;

    pinMode(YP, INPUT);
    pinMode(YM, INPUT);

    digitalWrite(YP, LOW);
    digitalWrite(YM, LOW);

    pinMode(XP, OUTPUT);
    pinMode(XM, OUTPUT);
    digitalWrite(XP, HIGH);
    digitalWrite(XM, LOW);

    for (i = 0; i < NUMSAMPLES; i++) {
        samples[i] = analogRead(YP);
    }
    insert_sort(samples, NUMSAMPLES);
    y = (1023 - samples[NUMSAMPLES / 2]); //choose median

    pinMode(XP, INPUT);
    pinMode(XM, INPUT);
    digitalWrite(XP, LOW);
    //digitalWrite(XM, LOW);     //.kbv for Due

    pinMode(YP, OUTPUT);
    digitalWrite(YP, HIGH);
    pinMode(YM, OUTPUT);
    //digitalWrite(YM, LOW);     //.kbv for Due

    for (i = 0; i < NUMSAMPLES; i++) {
        samples[i] = analogRead(XM);
    }

    insert_sort(samples, NUMSAMPLES);

    x = (1023 - samples[NUMSAMPLES / 2]);

    // Set X+ to ground
    pinMode(XP, OUTPUT);
    digitalWrite(XP, LOW);

    // Set Y- to VCC
    pinMode(YM, OUTPUT);     //.kbv
    digitalWrite(YM, HIGH);

    // Hi-Z X- and Y+
    digitalWrite(XM, LOW);   //.kbv
    pinMode(XM, INPUT);      //.kbv
    digitalWrite(YP, LOW);
    pinMode(YP, INPUT);

    int z1 = analogRead(XM);
    int z2 = analogRead(YP);

    z = (1023 - (z2 - z1));

    pinMode(YP, OUTPUT);
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);
    digitalWrite(XM, HIGH);

    return IMPoint(x, y, z);
}

IMPoint IMTouchScreen::getTouchPosition() {
    uint16_t xSum = 0, ySum = 0, zSum = 0;
    const int8_t waitLimit = 10;
    const int8_t divisorLimit = 8;
    int8_t divisor = 0;
    int8_t counter = waitLimit;
    int x = 0, y = 0, z = 0;
  
    do {
        IMPoint touch = getPoint();

        if (touch.z > LO_TRESHOLD && touch.z < HI_TRESHOLD) {
            if (divisor == divisorLimit) {
                xSum = xSum / divisorLimit;
                ySum = ySum / divisorLimit;
                zSum = zSum / divisorLimit;
                divisor = 1;
            }
            xSum += touch.x;
            ySum += touch.y;
            zSum += touch.z;
            divisor += 1;
            counter = waitLimit;
        } else {
            counter -= 1;
        }
        delay(10);
    } while (counter > 0);

    if (divisor) {
        x = xSum/divisor;
        y = ySum/divisor;
        z = zSum/divisor;
        
        x = map(x, TS_TOP, TS_BOT, 0, SCR_WIDTH);//landscape rotation
        y = map(y, TS_LEFT, TS_RT, 0, SCR_HEIGHT);
    }
    return IMPoint(x, y, z);
}
