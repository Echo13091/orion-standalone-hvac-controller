#pragma once

#include <ArduinoJson.h>

void setupSafety();
void updateSafety();
bool startupSafetyActive();
void appendSafetyJson(JsonDocument& doc);
