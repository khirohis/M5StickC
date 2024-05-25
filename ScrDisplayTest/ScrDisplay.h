#ifndef _SCR_DISPLAY_H_
#define _SCR_DISPLAY_H_

#define SCR_DISPLAY_ERROR (-1)
#define SCR_DISPLAY_NOERROR (0)

class ScrDisplay
{

private:
    struct DisplayMetrics {
        int mode = 0;
        int textSize = 0;
        int fontWidth = 0;
        int fontHeight = 0;

        int pixelWidth = 0;
        int pixelHeight = 0;

        int offsetX = 0;
        int offsetY = 0;
    } metrics;

    struct DisplayBuffer {
        int column = 0;
        int row = 0;
        char **buffer = NULL;
        int startOffset = 0;
    } buffer;

    struct Cursor {
        int x = 0;
        int y = 0;
    } cursor;

public:
    ScrDisplay();

    int init(int mode, int textSize);

    void clear();

    void setCursor(int x, int y);
    void lineFeed();

    int putChar(char ch);

private:
    void setupBuffer(int column, int row);
    void scrollBuffer();
    void flushBuffer();

    void drawChar(int x, int y, char ch);
};

#endif
