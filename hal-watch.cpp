
#include "hal.h"
#include "display.h"
#include "breakout-store.h"
#include "store.h"

const uint32_t palette[] = {
    0x000000,
    0x1D2B53,
    0x7E2553,
    0x008751,
    0xAB5236,
    0x5F574F,
    0xC2C3C7,
    0xFFF1E8,
    0xFF004D,
    0xFFA300,
    0xFFEC27,
    0x00E436,
    0x29ADFF,
    0x83769C,
    0xFF77A8,
    0xFFCCAA,
};

void HAL::init(void)
{
    getAButton();
    LGFX_Sprite *fb = Display::fb_sprite;

    fb->createSprite(DISP_X, DISP_Y);
    fb->clear(TFT_BLACK);
    fb->setColorDepth(4);
    for (uint8_t i = 0; i != 16; i++)
    {
        fb->setPaletteColor(i, palette[i]);
    }

    fb->fillSprite(0);
    fb->setFont(&DejaVu9);
}

void HAL::displaySetColor(uint8_t c)
{
    color = c;
}

void HAL::displaySetCursor(uint16_t x, uint16_t y)
{
    cursor_x = x;
    cursor_y = y;
}

void HAL::displayPrint(char *text)
{
    LGFX_Sprite *fb = Display::fb_sprite;
    fb->drawString(text, cursor_x, cursor_y);
}

void HAL::displayDrawBitmap(int16_t x0, int16_t y0, const uint8_t *data)
{
    LGFX_Sprite *fb = Display::fb_sprite;

    for (uint16_t y = 0; y != data[1]; y++)
    {
        for (uint16_t x = 0; x != data[0] / 2; x++)
        {
            uint8_t color = data[2 + y * data[0] / 2 + x] >> 4;
            if (color)
                fb->drawPixel(x0 + 2 * x, y0 + y, color);
            color = data[2 + y * data[0] / 2 + x] & 0x0f;
            if (color)
                fb->drawPixel(x0 + 2 * x + 1, y0 + y, color);
        }
    }
}

void HAL::displayDrawColumn(int16_t x, int16_t y, int16_t len)
{
    LGFX_Sprite *fb = Display::fb_sprite;
    fb->drawLine(x, y, x, y + len, color);
}

void HAL::displayDrawCircle(int16_t x, int16_t y, int16_t r)
{
    LGFX_Sprite *fb = Display::fb_sprite;
    fb->drawCircle(x, y, r, color);
}

void HAL::displayDrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    LGFX_Sprite *fb = Display::fb_sprite;
    fb->drawLine(x0, y0, x1, y1, color);
}

uint16_t HAL::getFontCharX(void)
{
    LGFX_Sprite *fb = Display::fb_sprite;
    uint x = DejaVu9.glyph->xAdvance;
    return x;
}

int16_t HAL::getPaddlePitch(void)
{

    int16_t pitch = GlobalState::pitch*2;
    if (pitch > 25)
        pitch = 25;
    if (pitch < -25)
        pitch = -25;

    return pitch;
}

uint32_t HAL::getTimeStamp(void)
{
    return xTaskGetTickCount() * 10;
}

bool HAL::getAButton(void)
{
    bool result = global_store.btn_cnt > last_btn ;

    last_btn = global_store.btn_cnt;
    return result;
}

int16_t HAL::getRandom(uint16_t max)
{
    return (rand() % max);
}