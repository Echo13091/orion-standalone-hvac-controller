#pragma once

#include <ArduinoJson.h>
#include "types.h"

void setupSensor();
void updateSensor();
SensorState getSensorState();
bool sensorHealthy();
void appendSensorJson(JsonDocument& doc);
