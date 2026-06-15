#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "globals.h"

void setupWifiAp() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(AP_IP, AP_GATEWAY, AP_SUBNET);

  bool ok = WiFi.softAP(AP_SSID, AP_PASSWORD);

  dnsServer.start(DNS_PORT, "*", AP_IP);

  Serial.println();
  Serial.println("=== Wi-Fi AP ===");
  Serial.print("AP start: ");
  Serial.println(ok ? "OK" : "FAILED");
  Serial.print("SSID: ");
  Serial.println(AP_SSID);
  Serial.print("Password: ");
  Serial.println(AP_PASSWORD);
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());
}

void handleWifi() {
  dnsServer.processNextRequest();
}
