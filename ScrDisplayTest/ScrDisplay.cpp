#include <M5StickC.h>
#include "ScrDisplay.h"

static const int sFontWidth = 6;
static const int sFontHeight = 8;

ScrDisplay::ScrDisplay()
{
}

int ScrDisplay::init(int mode)
{
    metrics.mode = mode;
    M5.Lcd.setRotation(mode);
    M5.Lcd.setTextFont(1);
    M5.Lcd.setTextSize(1);

    metrics.width = M5.Lcd.width();
    metrics.height = M5.Lcd.height();

    int column = metrics.width / sFontWidth;
    int row = metrics.height / sFontHeight;
    setupBuffer(column, row);

    clear();

    return SCR_DISPLAY_NOERROR;
}

void ScrDisplay::clear()
{
    M5.Lcd.fillScreen(BLACK);

    setCursor(0, 0);
}

void ScrDisplay::refresh()
{
    for (int row = 0; row < buffer.row; row++) {
        // TODO:
        M5.Lcd.setCursor(0, sFontHeight * row);
        M5.Lcd.print(buffer.buffer[row]);
    }
}

void ScrDisplay::setCursor(int x, int y)
{
    cursor.x = x;
    cursor.y = y;
}

void ScrDisplay::lineFeed()
{
    cursor.x = 0;
    if (++cursor.y >= buffer.row) {
        scrollBuffer();
        refresh();

        cursor.y--;
    }
}


int ScrDisplay::putChar(char ch)
{
    if (ch == '\n') {
        lineFeed();

        return 1;
    }

    buffer.buffer[cursor.y][cursor.x] = ch;
    drawChar(cursor.x, cursor.y, ch);

    if (cursor.x++ >= buffer.column) {
        lineFeed();
    }

    return 1;
}


void ScrDisplay::setupBuffer(int column, int row)
{
    if (buffer.buffer != NULL) {
        char **lines = buffer.buffer;
        for (int i = 0; i < buffer.row; i++) {
            free(*lines++);
        }
        free(buffer.buffer);
    }

    buffer.column = column;
    buffer.row = row;

    char **lines = (char **) malloc(sizeof(char *) * row);
    buffer.buffer = lines;
    int columnSize = sizeof(char) * (column + 1);
    for (int i = 0; i < row; i++) {
        char *chars = (char *) malloc(columnSize);
        *lines++ = chars;

        for (int j = 0; j < column; j++) {
            *chars++ = ' ';
        }
        *chars = '\0';
    }

    buffer.startOffset = 0;
}

void ScrDisplay::scrollBuffer()
{
    char **lines = buffer.buffer;
    char *chars = *lines;
    char **next = lines + 1;
    for (int i = 1; i < buffer.row; i++) {
        *lines++ = *next++;
    }

    *lines = chars;
    for (int i = 0; i < buffer.column; i++) {
        *chars++ = ' ';
    }
    *chars = '\0';
}

void ScrDisplay::drawChar(int x, int y, char ch)
{
    M5.Lcd.setCursor(sFontWidth * x, sFontHeight * y);
    M5.Lcd.print(ch);
}
