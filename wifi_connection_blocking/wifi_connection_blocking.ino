#include <Arduino.h>
#include <WiFiMulti.h>

#define WIFI_SSID "esp32"
#define WIFI_PASSWORD "mali2001"
#define LED_BUILTIN 22

WiFiMulti wifiMulti;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  Serial.println("Connected");
}

void loop() {
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
}