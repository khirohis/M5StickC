#include <M5StickC.h>

void setup() {
  M5.begin();

  pinMode(M5_LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(M5_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second

  digitalWrite(M5_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second
}
