void httpAudioTask(void *parameter) {
  
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
  
  while (true) {
    
    unsigned long now = millis();

  if (now - lastUpdateTime > refreshInterval) {
    lastUpdateTime = now;
    fetchAircraftData();
  }
  if(distance <= 70) refreshInterval = refreshInterval_fast;
  else refreshInterval = refreshInterval_slow;
    delay(10);
  }
}
