
void setLEDBlink(int l3, int l2, int l1) {
  if (l3 > 0) {
    //maxBlinks = 6;    // 3 full blinks (ON+OFF)
    blinkDelay = 100;
  } else if (l2 > 0) {
    //maxBlinks = 4;    // 2 full blinks
    blinkDelay = 300;
  } else if (l1 > 0) {
    //maxBlinks = 2;    // 1 full blink
    blinkDelay = 600;
  } else {
    ledState = LED_IDLE;
    digitalWrite(ledPin, LOW);
    return;
  }

  // Start blinking
//  blinkCount = 0;
  ledOn = false;
  lastBlinkTime = millis();
  ledState = LED_BLINKING;
}
