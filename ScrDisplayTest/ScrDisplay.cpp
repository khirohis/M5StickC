#include <M5StickC.h>
#include "ScrDisplay.h"

static const int sFontWidth = 6;
static const int sFontHeight = 8;

ScrDisplay::ScrDisplay()
{
}

int ScrDisplay::init()
{
    M5.Lcd.setTextFont(1);
    M5.Lcd.setTextSize(1);

    return setMode(0);
}

uint8_t ScrDisplay::getMode()
{
    return mode;
}

int ScrDisplay::setMode(uint8_t newMode)
{
    mode = newMode;

    // setup modes
    M5.Lcd.setRotation(mode);

    width = M5.Lcd.width();
    height = M5.Lcd.height();
    numColumn = width / sFontWidth;
    numRow = height / sFontHeight;

    // cleanup display
    clear();
    setCursor(0, 0);

    return SCR_DISPLAY_NOERROR;
}

void ScrDisplay::clear()
{
    M5.Lcd.fillScreen(BLACK);
}

void ScrDisplay::setCursor(int16_t x, int16_t y)
{
    cursorX = x;
    cursorY = y;
    M5.Lcd.setCursor(sFontWidth * x, sFontHeight * y);
}

int ScrDisplay::putChar(char ch)
{
    if (ch == '\n') {
        lineFeed();

        return 1;
    }

    M5.Lcd.print(ch);
    cursorX++;

    if (cursorX >= numColumn) {
        lineFeed();
    }

    return 1;
}

void ScrDisplay::lineFeed()
{
    cursorX = 0;
    if (++cursorY >= numRow) {
        // TODO: scroll

        cursorY--;
    }

    setCursor(cursorX, cursorY);
}
