#include <Arduino.h>

#include "safety.h"
#include "config.h"
#include "globals.h"

static bool startupActive = true;

void setupSafety() {
  startupActive = true;
}

void updateSafety() {
  if (startupActive && millis() - bootMillis >= STARTUP_SAFETY_DELAY_MS) {
    startupActive = false;
  }
}

bool startupSafetyActive() {
  return startupActive;
}

void appendSafetyJson(JsonDocument& doc) {
  JsonObject safety = doc["safety"].to<JsonObject>();

  safety["startup_safety_active"] = startupSafetyActive();
  safety["startup_safety_delay_ms"] = STARTUP_SAFETY_DELAY_MS;
  safety["uptime_ms"] = millis();
}
