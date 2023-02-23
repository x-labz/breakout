#include <Pokitto.h>
#include <PokittoFonts.h>
#include "hal.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void HAL::init(void) {
    PD::persistence = false;
    PD::loadRGBPalette(palettePico);
    PD::setFont(fontZXSpec);
    PD::setInvisibleColor(0);
}

void HAL::displaySetColor(uint8_t color) {
    PD::setColor(color);
}

void HAL::displaySetCursor(uint16_t x, uint16_t y) {
    PD::setCursor(x, y);
}

void HAL::displayPrint(char * text) {
    PD::print(text);
}

void HAL::displayDrawBitmap(int16_t x, int16_t y,
    const uint8_t * data) {
    PD::drawBitmap(x, y, data);
}

void HAL::displayDrawColumn(int16_t x, int16_t y, int16_t len) {
    PD::drawColumn(x, y, len);
}

void HAL::displayDrawCircle(int16_t x, int16_t y, int16_t r) {
    PD::drawCircle(x, y, r);
}

void HAL::displayDrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
    PD::drawLine(x0, y0, x1, y1);
}

void HAL::displayDrawRect(int16_t x0, int16_t y0, int16_t w, int16_t h) {
    if (w > 2) {
        PD::drawLine(x0 + (w > 2 ? 1 : 0), y0, x0 + w - (w > 2 ? 2 : 0), y0);
        PD::drawLine(x0 + (w > 2 ? 1 : 0), y0 + h, x0 + w - (w > 2 ? 2 : 0), y0 + h);
    }
    if (h > 2) {
        PD::drawLine(x0, y0 + (h > 2 ? 1 : 0), x0, y0 + h - (h > 2 ? 2 : 0));
        PD::drawLine(x0 + w, y0 + (h > 2 ? 1 : 0), x0 + w, y0 + h - (h > 2 ? 2 : 0));
    }
}

uint16_t HAL::getFontCharX(void) {
    return fontZXSpec[0];
}

int16_t HAL::getPaddlePitch(void) {

    if (PC::buttons.leftBtn()) {
        return -10;
    }
    if (PC::buttons.rightBtn()) {
        return 10;
    }
    return 0;
}

uint32_t HAL::getTimeStamp(void) {
    return PC::getTime();
}

bool HAL::getAButton(void) {
    bool btn = PC::buttons.aBtn();
    bool result = btn != lastAButton && btn == true;
    lastAButton = btn;
    return result;
}

int16_t HAL::getRandom(uint16_t max) {
    return (rand() % max);
}