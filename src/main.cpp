#include <Arduino.h>

#include "config.h"
#include "globals.h"
#include "wifi_manager.h"
#include "api_server.h"
#include "relay_control.h"
#include "safety.h"

void setup() {
  Serial.begin(115200);
  delay(500);

  bootMillis = millis();
  lastMode = "booting";

  pinMode(STATUS_LED_PIN, OUTPUT);
  digitalWrite(STATUS_LED_PIN, LOW);

  setupSafety();

  bool relayOk = setupRelays();
  if (!relayOk) {
    lastMode = "fault";
  }

  setupWifiAp();
  setupRoutes();
  server.begin();

  if (relayOk) {
    lastMode = "setup_ap";
  }

  Serial.println();
  Serial.println("Orion Standalone HVAC Controller");
  Serial.print("Firmware: ");
  Serial.println(FIRMWARE_VERSION);
  Serial.print("AP SSID: ");
  Serial.println(AP_SSID);
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("Open http://192.168.4.1");
}

void loop() {
  handleWifi();
  server.handleClient();
  updateSafety();

  static unsigned long lastBlink = 0;
  static bool led = false;

  if (millis() - lastBlink > 1000) {
    lastBlink = millis();
    led = !led;
    digitalWrite(STATUS_LED_PIN, led ? HIGH : LOW);
  }
}
