#include <M5StickC.h>
#include "ScrDisplay.h"

static ScrDisplay disp;

void setup() {
    M5.begin();

    // シリアルの初期化
    Serial.begin(115200);

    disp.init();
    disp.setMode(1);
    disp.setCursor(1, 1);
}

void loop() {
    int ch = Serial.read();
    if (ch >= 0) {
        disp.putChar(ch);
    }
}
