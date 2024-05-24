#include <M5StickC.h>

void setup() {
  M5.begin();

  // シリアルの初期化
  Serial.begin(115200);
  Serial.println("Start");

  // 内臓LCDの初期化
  M5.Lcd.setRotation(0);
  M5.Lcd.setTextFont(1);    // 8pixel font
  M5.Lcd.setTextSize(1);    // multiplier
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);

  // 内臓LEDの初期化
  pinMode(M5_LED, OUTPUT);
}

void loop() {
  M5.update();

  if (M5.BtnA.isPressed()) {
    lcdPrintln("1234567890123");
    digitalWrite(M5_LED, LOW);
    delay(200);
  } else {
    digitalWrite(M5_LED, HIGH);
  }

  if (M5.BtnB.isPressed()) {
    lcdPrintln("12345678901234");
    digitalWrite(M5_LED, LOW);
    delay(100);
    digitalWrite(M5_LED, HIGH);
    delay(100);
  } else {
    digitalWrite(M5_LED, HIGH);
  }
}

static int line = 0;
static const int maxColumn = 13;
static const int maxRow = 20;

void lcdPrintln(const char* str) {
  if (line >= maxRow) {
    line = 0;
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
  }

  // TODO: 最終行の2行目以降が捨てられる
  size_t size = M5.Lcd.println(str);

  // sizeは文字数に2byteプラスされる (2)
  // maxColumn文字数で割り切れる場合は最後に改行されない分の補正 (1)
  // マイナス文字数となっても0になるので判定は端折る
  size -= 3;
  line += size / maxColumn + 1;
}