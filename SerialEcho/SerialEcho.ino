#include <M5StickC.h>

void setup() {
    M5.begin();

    // シリアルの初期化
    Serial.begin(115200);

      // 内臓LCDの初期化
    M5.Lcd.setRotation(1);
    M5.Lcd.setTextFont(1);    // 8pixel font
    M5.Lcd.setTextSize(1);    // multiplier
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
}

void loop() {
    /*
    String line = Serial.readString();
    if (line.length() > 0) {
        Serial.println(line.length());
        Serial.println((int)line.charAt(line.length() - 1));
        M5.Lcd.print(line);
    }
     */
    int ch = Serial.read();
    if (ch >= 0) {
        M5.Lcd.print((char)ch);
    }
}
