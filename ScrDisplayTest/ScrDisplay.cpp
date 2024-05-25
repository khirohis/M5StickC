#include <M5StickC.h>
#include "ScrDisplay.h"

static const int sFontWidth = 6;
static const int sFontHeight = 8;

ScrDisplay::ScrDisplay()
{
}

int ScrDisplay::init(int mode, int textSize)
{
    metrics.mode = mode;
    metrics.textSize = textSize;
    metrics.fontWidth = sFontWidth * textSize;
    metrics.fontHeight = sFontHeight * textSize;

    M5.Lcd.setRotation(mode);
    M5.Lcd.setTextFont(1);
    M5.Lcd.setTextSize(textSize);

    metrics.pixelWidth = M5.Lcd.width();
    metrics.pixelHeight = M5.Lcd.height();

    int column = metrics.pixelWidth / metrics.fontWidth;
    metrics.offsetX = (metrics.pixelWidth % metrics.fontWidth) / 2;
    int row = metrics.pixelHeight / metrics.fontHeight;
    metrics.offsetY = (metrics.pixelHeight % metrics.fontHeight) / 2;
    setupBuffer(column, row);

    clear();

    return SCR_DISPLAY_NOERROR;
}

void ScrDisplay::clear()
{
    M5.Lcd.fillScreen(BLACK);

    setCursor(0, 0);
}

void ScrDisplay::setCursor(int x, int y)
{
    cursor.x = x;
    cursor.y = y;
}

int ScrDisplay::putChar(char ch)
{
    if (ch == '\n') {
        lineFeed();

        return 1;
    }

    buffer.buffer[cursor.y][cursor.x] = ch;
    drawChar(cursor.x, cursor.y, ch);

    if (++cursor.x >= buffer.column) {
        lineFeed();
    }

    return 1;
}

void ScrDisplay::lineFeed()
{
    cursor.x = 0;
    if (++cursor.y >= buffer.row) {
        scrollBuffer();
        flushBuffer();

        cursor.y--;
    }
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

void ScrDisplay::flushBuffer()
{
    for (int row = 0; row < buffer.row; row++) {
        // TODO:
        M5.Lcd.setCursor(metrics.offsetX,
            metrics.offsetY + metrics.fontHeight * row);
        M5.Lcd.print(buffer.buffer[row]);
    }
}


void ScrDisplay::drawChar(int x, int y, char ch)
{
    M5.Lcd.setCursor(metrics.offsetX + metrics.fontWidth * x,
        metrics.offsetY + metrics.fontHeight * y);
    M5.Lcd.print(ch);
}
