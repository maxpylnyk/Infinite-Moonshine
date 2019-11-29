#ifndef IM_ERRORS_PANE_H
#define IM_ERRORS_PANE_H

#include "IMPane.h"
#include "utilities/IMErrors.h"

class IMErrorsPane : public IMPane {
  private:
    IMErrors * errors;

  public:
    IMErrorsPane(IMTFT * tft, IMCaptions * captions)
      : IMPane(tft, captions, 0) {};

    void setErrors(IMErrors * list) {
      errors = list;
    }

    void draw() {
      uint8_t count = errors->getCount();
      uint8_t offset = WIDTH_MULT * ERR_FONT_SIZE / 2;
      int x0 = 0;
      int y0 = SCR_HEIGHT - BAR_HEIGHT;
      IMRect header = IMRect(x0, y0, SCR_WIDTH, SCR_HEIGHT);
      getTFT()->paintBackground();
      getTFT()->setColor(ERROR_COLOR);
      getTFT()->fillRect(header);
      getTFT()->print(getCaptions()->ERRORS, HDR_FONT_SIZE, BACKGROUND_COLOR, header);
      x0 += offset;

      if (count) {
        for (int i = 0; i < count; i++) {
          IMError error = (IMError) errors->get(i);
          y0 += HEIGHT_MULT * ERR_FONT_SIZE + offset;

          switch(error) {
            case OVERFLOW :
              getTFT()->print(getCaptions()->OVERFLOW, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_HLVL :
              getTFT()->print(getCaptions()->NO_HLVL, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_CONNECTION :
              getTFT()->print(getCaptions()->NO_CONNECTION, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_SD_CARD :
              getTFT()->print(getCaptions()->NO_SD_CARD, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_SD_SPACE :
              getTFT()->print(getCaptions()->NO_SD_SPACE, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_OUT_MTR :
              getTFT()->print(getCaptions()->NO_OUT_MTR, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_RET_MTR :
              getTFT()->print(getCaptions()->NO_RET_MTR, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_COND_MTR :
              getTFT()->print(getCaptions()->NO_COND_MTR, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_SW :
              getTFT()->print(getCaptions()->NO_SW, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_ALC :
              getTFT()->print(getCaptions()->NO_ALC, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_BAR :
              getTFT()->print(getCaptions()->NO_BAR, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_RTC :
              getTFT()->print(getCaptions()->NO_RTC, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_STEAM_TRM :
              getTFT()->print(getCaptions()->NO_STEAM_TRM, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_PIPE_TRM :
              getTFT()->print(getCaptions()->NO_PIPE_TRM, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_COND_TRM :
              getTFT()->print(getCaptions()->NO_COND_TRM, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_ENV_TRM :
              getTFT()->print(getCaptions()->NO_ENV_TRM, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NO_HEAT :
              getTFT()->print(getCaptions()->NO_HEAT, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case NANO_BLACKOUT :
              getTFT()->print(getCaptions()->NANO_BLACKOUT, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case MEGA_BLACKOUT :
              getTFT()->print(getCaptions()->MEGA_BLACKOUT, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
            case TRANSMISSION_CORRUPTED :
              getTFT()->print(getCaptions()->TRANSMISSION_CORRUPTED, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
              break;
          }
        }
      } else {
        getTFT()->print(getCaptions()->NO_ERROR, ERR_FONT_SIZE, TEXT_COLOR, x0, y0);
      }
    }

    void handleTouch() {}
    void refresh() {
      //draw();
    }

};

#endif
