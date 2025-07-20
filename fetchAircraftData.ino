void fetchAircraftData() {
  String url = "https://opensky-network.org/api/states/all?lamin=" + String(lamin, 2) +
               "&lomin=" + String(lomin, 2) +
               "&lamax=" + String(lamax, 2) +
               "&lomax=" + String(lomax, 2);

  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();

  if (httpCode <= 0) {
    Serial.println("HTTP Request failed.");
    system_error = true;
    http.end();
    return;
  }
  
  String payload = http.getString();
  http.end();

  DynamicJsonDocument doc(35000); // Large enough buffer
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    Serial.println("JSON parsing failed!");
    system_error = true;
    return;
  }

  JsonArray states = doc["states"].as<JsonArray>();

  int count1 = 0, count2 = 0, count3 = 0;

  Serial.println("Aircraft within 70 km:");
  Serial.println("--------------------------------------------------");

  for (JsonArray state : states) {
    double lon = state[5] | 0.0;
    double lat = state[6] | 0.0;
    double alt = state[7] | 0.0;

    if (lat == 0.0 && lon == 0.0) continue;

    distance = haversine(userLat, userLon, lat, lon);

    if (distance <= maxRadiusKm) {
      String callsign = state[1] | "UNKNOWN";
      String country = state[2] | "UNKNOWN";
      bool isDomestic = (alt < 12000); // Approx threshold

      if (distance <= 30) count3++;
      else if (distance <= 50) count2++;
      else count1++;

      Serial.printf("Callsign: %-8s | Country: %-12s | Dist: %6.1f km | Alt: %6.0f m | %s\n",
                    callsign.c_str(), country.c_str(), distance, alt,
                    isDomestic ? "Domestic" : "International");
    }
  }

  Serial.println("--------------------------------------------------");
  Serial.printf("Breach Summary:\n");
  Serial.printf("  Level 3 (<30km): %d\n", count3);
  Serial.printf("  Level 2 (<50km): %d\n", count2);
  Serial.printf("  Level 1 (<70km): %d\n\n", count1);

  setLEDBlink(count3, count2, count1);
  
  if (count3 > 0) AudioWarning(audioData_level3breach, audioLength_level3breach, sampleRate);
  else if (count2 > 0)  AudioWarning(audioData_level2breach, audioLength_level2breach, sampleRate);
  else if (count1 > 0)  AudioWarning(audioData_level1breach, audioLength_level1breach, sampleRate);
  system_error = false;
}
