void ledTask(void *parameter) {
  while (true) {
    unsigned long now = millis();
    
  // Handle non-blocking LED blinking
  if(!system_error){
      if (ledState == LED_BLINKING) {
  //if (ledState == LED_BLINKING && !system_error) {
    if (now - lastBlinkTime >= blinkDelay) {
      lastBlinkTime = now;
      ledOn = !ledOn;
      digitalWrite(ledPin, ledOn ? HIGH : LOW);
      /*blinkCount++;
      if (blinkCount >= maxBlinks) {
        ledState = LED_IDLE;
        digitalWrite(ledPin, LOW);
      }*/
    }
  }
  else digitalWrite(ledPin, LOW);
  }
  else digitalWrite(ledPin, HIGH);

   delay(10);
  }
}
