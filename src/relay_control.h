#pragma once

#include <ArduinoJson.h>
#include "types.h"

bool setupRelays();
void allRelaysOff(const char* reason);
void applyRelayState();
RelayState getRelayState();
bool relayAnyActive();
void appendRelayJson(JsonDocument& doc);
