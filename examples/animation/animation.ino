#include <UTFTGLUE.h>
#include <SD.h>
#include <TouchScreen.h>

#include <Fonts/FreeSans18pt7b.h>
//#include <FreeDefaultFonts.h>

double INFINITY_WIDTH_MULTIPLIER = 0.8625;
double BAR_HEIGHT_MULTIPLIER = 0.2959;
double BUTTONS_WIDTH_MULTIPLIER = 0.2219;

const uint32_t MAIN_COLOR =         0x94ffe6;
const uint32_t MAIN_COLOR_FLAT =    0x3e6b62;
const uint32_t HEAT_COLOR =         0xfff700;
const uint32_t STAB_COLOR =         0xff7700;
const uint32_t HEAD_COLOR =         0xff0000;
const uint32_t AROMA_COLOR =        0xff00ff;
const uint32_t BODY_COLOR =         0xffffff;
const uint32_t TAIL_COLOR =         0x0088ff;
const uint32_t BACKGROUND_COLOR =   0x000000;

const uint16_t TS_LEFT = 942;
const uint16_t TS_RT  = 186;
const uint16_t TS_TOP = 927;
const uint16_t TS_BOT = 183;

const int16_t LO_TRESHOLD = 20;
const int16_t HI_TRESHOLD = 1000;
const uint8_t YP = A1;
const uint8_t XM = A2;
const uint8_t YM = 7;
const uint8_t XP = 6;
const uint8_t SD_CS = 10;

int8_t LINE_WIDTH = 2;
int8_t LINE_RADIUS = LINE_WIDTH / 2;

UTFTGLUE screen(0x0154,A2,A1,A3,A4,A0);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

void setup() {
  Serial.begin(9600);
  screen.InitLCD();
  screen.cp437(true);

  if (!SD.begin(SD_CS)) {
    Serial.print(F("cannot start SD"));
    while (1);
  }
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  paintBackground();
  drawInfinity(MAIN_COLOR);
  drawInfoButton();
  drawCancelButton();
  drawBottomLine();
  printState();
}

void loop() {
  handleTouch();
}

TSPoint scanTouch(void) {
  TSPoint out;
  
  tp = ts.getPoint();
  out = TSPoint(tp.x, tp.y, tp.z);
  
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);  //because TFT control pins
  digitalWrite(XM, HIGH);
  
  return out;
}

TSPoint getTouchPosition() {
  uint16_t xSum = 0, ySum = 0, zSum = 0;
  const int8_t waitLimit = 10;
  const int8_t divisorLimit = 8;
  int8_t divisor = 0;
  int8_t counter = waitLimit;
  
  do {
    TSPoint touch = scanTouch();

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
    return TSPoint(xSum/divisor, ySum/divisor, zSum/divisor);
  }
  return TSPoint();
}

void handleTouch() {
  TSPoint touch = getTouchPosition();

  if (touch.hasValue()) {
    int16_t x = map(touch.y, TS_LEFT, TS_RT, 0, screen.width());
    int16_t y = map(touch.x,TS_BOT, TS_TOP, 0, screen.height());

    //Serial.println(String(x)+" "+String(y));
    
    int buttonWidth = screen.width() * BUTTONS_WIDTH_MULTIPLIER;
    int infoXStart = screen.width() - buttonWidth;
    int cancelXEnd = buttonWidth;
    int topYStart = screen.height() - buttonWidth;
    int barYEnd = screen.height() * BAR_HEIGHT_MULTIPLIER;

    if (y < barYEnd) {
      bottomBarPressed();
    } else if (y > topYStart) {
      if (x < cancelXEnd) {
        cancelPressed();
      } else if (x > infoXStart) {
        infoPressed();
      }
    }
  }
}

void cancelPressed() {
  Serial.println("cancel pressed");
}

void infoPressed() {
  Serial.println("info pressed");
}

void bottomBarPressed() {
  Serial.println("bottom pressed");
}

void paintBackground() {
  screen.fillScreen(BACKGROUND_COLOR);
}

void drawInfinity(uint32_t color) {
  int crt2 = screen.width() * INFINITY_WIDTH_MULTIPLIER / 2;
  int xCenter = screen.width() / 2;
  int yCenter = screen.height() / 2;
  double x, y;
  double p;
  double p2;
  double p3;
  double p4;

  setColor(color);
  //setColor(HEAT_COLOR);

  //INIT STATE
  for (p = 100; p > 10; p -= 1) {
    p2 = p * p;
    p3 = p2 * p;
    p4 = p3 * p;

    x = xCenter + crt2 * (p + p3) / (1 + p4);
    y = yCenter + crt2 * (p - p3) / (1 + p4);
    screen.fillCircle(x, y, LINE_RADIUS);
  }//STAB STATE
  //setColor(STAB_COLOR);

  for (p = 10; p > 6; p -= 0.05) {
    p2 = p * p;
    p3 = p2 * p;
    p4 = p3 * p;

    x = xCenter + crt2 * (p + p3) / (1 + p4);
    y = yCenter + crt2 * (p - p3) / (1 + p4);
    screen.fillCircle(x, y, LINE_RADIUS);
  }//HEAD STATE
  //setColor(HEAD_COLOR);

  for (p = 6; p > 3; p -= 0.05) {
    p2 = p * p;
    p3 = p2 * p;
    p4 = p3 * p;

    x = xCenter + crt2 * (p + p3) / (1 + p4);
    y = yCenter + crt2 * (p - p3) / (1 + p4);
    screen.fillCircle(x, y, LINE_RADIUS);
  }
  //PRE_BODY STATE
  //setColor(AROMA_COLOR);

  for (p = 3; p > 2; p -= 0.01) {
    p2 = p * p;
    p3 = p2 * p;
    p4 = p3 * p;

    x = xCenter + crt2 * (p + p3) / (1 + p4);
    y = yCenter + crt2 * (p - p3) / (1 + p4);
    screen.fillCircle(x, y, LINE_RADIUS);
  }
  //BODY STATE
  //setColor(BODY_COLOR);

  for (p = 2; p > -5; p -= 0.01) {
    p2 = p * p;
    p3 = p2 * p;
    p4 = p3 * p;

    x = xCenter + crt2 * (p + p3) / (1 + p4);
    y = yCenter + crt2 * (p - p3) / (1 + p4);
    screen.fillCircle(x, y, LINE_RADIUS);
  }
  //PRE_TAIL STATE
  //setColor(TAIL_COLOR);

  for (p = -5; p > -10; p -= 0.05) {
    p2 = p * p;
    p3 = p2 * p;
    p4 = p3 * p;

    x = xCenter + crt2 * (p + p3) / (1 + p4);
    y = yCenter + crt2 * (p - p3) / (1 + p4);
    screen.fillCircle(x, y, LINE_RADIUS);
  }
  //FINISH STATE
  //setColor(color);

  for (p = -10; p > -100; p -= 1) {
    p2 = p * p;
    p3 = p2 * p;
    p4 = p3 * p;

    x = xCenter + crt2 * (p + p3) / (1 + p4);
    y = yCenter + crt2 * (p - p3) / (1 + p4);
    screen.fillCircle(x, y, LINE_RADIUS);
  }
}

void setColor(uint32_t color) {
  byte r, g, b;

  r = (color & 0xFF0000) >> 16;
  g = (color & 0xFF00) >> 8;
  b = color & 0xFF;

  screen.setColor(r, g, b);
}

void drawInfoButton() {
  int16_t radius = 15;
  int16_t edgeOffset = 20;
  int16_t lineHeight = 8;
  int16_t xCenter = screen.width() - edgeOffset - radius;
  int16_t yCenter = edgeOffset + radius;
  int16_t xDot = xCenter;
  int16_t yDot = 28;
  int16_t xLine = xDot;
  int16_t yLineTop = 35;
  int16_t yLineBottom = yLineTop + lineHeight;

  setColor(MAIN_COLOR);
  
  for (int8_t i = 0; i < LINE_WIDTH; i++) {
    screen.drawCircle(xCenter, yCenter, radius);
    radius -= 1;
  }
  for (int y = yLineTop; y < yLineBottom; y++) {
    screen.drawCircle(xCenter, y, LINE_RADIUS);
  }
  screen.fillCircle(xDot, yDot, LINE_RADIUS);
}

void drawCancelButton() {
  int16_t edgeOffset = 23;
  int16_t size = 20;
  int16_t xTop = edgeOffset;
  int16_t yTop = edgeOffset;
  int16_t xBottom = edgeOffset + size;
  int16_t yBottom = edgeOffset + size;

  setColor(MAIN_COLOR);

  for (int8_t i = 0; i < LINE_WIDTH; i++) {
    screen.drawLine(xTop, yTop, xBottom, yBottom);
    xTop += 1;
    xBottom += 1;
  }

  xTop = edgeOffset + size;
  yTop = edgeOffset;
  xBottom = edgeOffset;
  yBottom = edgeOffset + size;

  for (int8_t i = 0; i < LINE_WIDTH; i++) {
    screen.drawLine(xTop, yTop, xBottom, yBottom);
    xTop += 1;
    xBottom += 1;
  }
}

void eraseCancelButton() {
  int16_t squareSize = screen.height() * BAR_HEIGHT_MULTIPLIER;
  
  setColor(BACKGROUND_COLOR);
  screen.fillRect(0, 0, squareSize, squareSize);
}

void drawBottomLine() {
  int y = screen.height() - 43;
  int wd = screen.width() * INFINITY_WIDTH_MULTIPLIER;
  int xStart = (screen.width() - wd) / 2;
  int xEnd = xStart + wd;

  for (int8_t i = 0; i < LINE_WIDTH; i++) {
    screen.drawLine(xStart, y, xEnd, y);
    y += 1;
  }
}

void printState() {
  screen.setFont(NULL);
  setColor(MAIN_COLOR);
  screen.setTextSize(2);
  screen.print(utf8rus("Ректификация"), 90, screen.height() - 25);
}

String utf8rus(String source)
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}
