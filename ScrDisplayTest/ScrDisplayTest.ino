#include <M5StickC.h>
#include "ScrDisplay.h"

static ScrDisplay disp;

void setup() {
    M5.begin();

    // シリアルの初期化
    Serial.begin(115200);

    disp.init(1, 2);
}

void loop() {
    int ch = Serial.read();
    if (ch >= 0) {
        disp.putChar(ch);
    }
}
