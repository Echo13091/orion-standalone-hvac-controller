#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#include "api_server.h"
#include "config.h"
#include "globals.h"
#include "web_page.h"

static void sendJson(int code, const String& body) {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET,POST,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  server.send(code, "application/json", body);
}

static String statusJson() {
  JsonDocument doc;

  doc["ok"] = true;
  doc["device"] = DEVICE_NAME;
  doc["firmware_version"] = FIRMWARE_VERSION;
  doc["mode"] = lastMode;
  doc["uptime_seconds"] = millis() / 1000;

  JsonObject ap = doc["ap"].to<JsonObject>();
  ap["ssid"] = AP_SSID;
  ap["ip"] = WiFi.softAPIP().toString();
  ap["clients"] = WiFi.softAPgetStationNum();

  JsonObject hvac = doc["hvac"].to<JsonObject>();
  hvac["ready"] = false;
  hvac["message"] = "Relay and sensor layers not enabled yet.";

  String out;
  serializeJson(doc, out);
  return out;
}

static void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

static void handleStatus() {
  sendJson(200, statusJson());
}

static void handleOptions() {
  sendJson(200, "{\"ok\":true}");
}

static void handleNotFound() {
  server.sendHeader("Location", String("http://") + AP_IP.toString() + "/", true);
  server.send(302, "text/plain", "");
}

void setupRoutes() {
  server.on("/", HTTP_GET, handleRoot);

  server.on("/api/status", HTTP_GET, handleStatus);
  server.on("/api/status", HTTP_OPTIONS, handleOptions);

  server.on("/generate_204", HTTP_GET, handleRoot);
  server.on("/gen_204", HTTP_GET, handleRoot);
  server.on("/hotspot-detect.html", HTTP_GET, handleRoot);
  server.on("/connecttest.txt", HTTP_GET, handleRoot);
  server.on("/fwlink", HTTP_GET, handleRoot);
  server.on("/success.txt", HTTP_GET, handleRoot);

  server.onNotFound(handleNotFound);
}
