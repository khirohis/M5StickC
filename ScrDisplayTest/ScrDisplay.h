#ifndef _SCR_DISPLAY_H_
#define _SCR_DISPLAY_H_

#define SCR_DISPLAY_ERROR (-1)
#define SCR_DISPLAY_NOERROR (0)

class ScrDisplay
{

private:
    uint8_t mode = 0;

    int width = 0;
    int height = 0;
    int numColumn = 0;
    int numRow = 0;

    int cursorX = 0;
    int cursorY = 0;

public:
    ScrDisplay();

    int init();

    uint8_t getMode();
    int setMode(uint8_t newMode);

    void clear();

    void setCursor(int16_t x, int16_t y);

    int putChar(char ch);

private:
    void lineFeed();
};

#endif
