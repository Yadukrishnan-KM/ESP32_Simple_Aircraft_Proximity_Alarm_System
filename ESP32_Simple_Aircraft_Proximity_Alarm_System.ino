#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "level1breach.h"
#include "level2breach.h"
#include "level3breach.h"

// Audio warning variables
extern const size_t audioLength_level1breach;
extern const size_t audioLength_level2breach;
extern const size_t audioLength_level3breach;
const int sampleRate = 8000; // Hz
const int dacPin = 25;       // DAC1 = GPIO25

// -------- Wi-Fi Credentials --------
const char* ssid = "OnePlus NordCE 5G";
const char* password = "c67hu553";

// -------- User Location (Dharwad Precise) --------
const double userLat = 15.48515823806643;
const double userLon = 74.9363912718834;
const double maxRadiusKm = 70.0;

// -------- Bounding Box (~70 km radius) --------
const double lamin = 14.8551;
const double lomin = 74.2863;
const double lamax = 16.1151;
const double lomax = 75.5863;


// -------- LED Pin (ESP32 DevKit V1 built-in LED) --------
const int ledPin = 2;

// -------- Refresh Interval (milliseconds) --------
const unsigned long refreshInterval_fast = 10000; // 10 seconds
const unsigned long refreshInterval_slow = 60000; // 60 seconds
unsigned long refreshInterval = refreshInterval_fast;
unsigned long lastUpdateTime = 0;
double distance = 0;

// -------- LED Blink State Machine --------
enum LedState { LED_IDLE, LED_BLINKING };
LedState ledState = LED_IDLE;

//int blinkCount = 0;
//int maxBlinks = 0;
int blinkDelay = 0;
bool ledOn = false;
unsigned long lastBlinkTime = 0;
bool system_error = true;

TaskHandle_t TaskHTTP;
TaskHandle_t TaskLED;

void setup() {
  
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  xTaskCreatePinnedToCore(
  httpAudioTask,
  "HTTP-Audio Task",
  16384,         // 64 KB (in words)
  NULL,
  1,
  &TaskHTTP,
  0              // Core 0
);

xTaskCreatePinnedToCore(
  ledTask,
  "LED Task",
  2048,
  NULL,
  1,
  &TaskLED,
  1              // Core 1
);

}

void loop() {
  

}
