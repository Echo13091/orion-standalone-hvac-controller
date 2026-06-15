#include <Arduino.h>
#include <DHT.h>

#include "sensor.h"
#include "config.h"

static DHT dht(DHT_PIN, DHT_TYPE == 22 ? DHT22 : DHT11);
static SensorState sensorState;

static bool validSensorReading(float tempF, float humidity) {
  if (isnan(tempF) || isnan(humidity)) return false;
  if (tempF < MIN_VALID_TEMP_F || tempF > MAX_VALID_TEMP_F) return false;
  if (humidity < MIN_VALID_HUMIDITY || humidity > MAX_VALID_HUMIDITY) return false;
  return true;
}

static bool readSensorNow() {
  float tempF = NAN;
  float humidity = NAN;

  for (int attempt = 0; attempt < 3; attempt++) {
    tempF = dht.readTemperature(true);
    humidity = dht.readHumidity();

    Serial.print("DHT attempt ");
    Serial.print(attempt + 1);
    Serial.print(" tempF=");
    Serial.print(tempF);
    Serial.print(" humidity=");
    Serial.println(humidity);

    if (validSensorReading(tempF, humidity)) {
      sensorState.ok = true;
      sensorState.temperatureF = tempF;
      sensorState.humidity = humidity;
      sensorState.status = "ok";
      sensorState.faultMessage = "";
      sensorState.lastReadMs = millis();
      return true;
    }

    delay(250);
  }

  sensorState.ok = false;
  sensorState.status = "fault";
  sensorState.faultMessage = "DHT sensor read failed or returned invalid data.";
  sensorState.lastReadMs = millis();

  return false;
}

void setupSensor() {
  dht.begin();
  delay(1500);

  sensorState.status = "initializing";
  readSensorNow();

  Serial.println();
  Serial.println("=== HVAC Sensor ===");
  Serial.print("DHT GPIO: ");
  Serial.println(DHT_PIN);
  Serial.print("DHT type: ");
  Serial.println(DHT_TYPE == 22 ? "DHT22" : "DHT11");
  Serial.print("Sensor status: ");
  Serial.println(sensorState.status);
}

void updateSensor() {
  unsigned long now = millis();

  if (sensorState.lastReadMs == 0 || now - sensorState.lastReadMs >= SENSOR_READ_INTERVAL_MS) {
    readSensorNow();
  }
}

SensorState getSensorState() {
  return sensorState;
}

bool sensorHealthy() {
  return sensorState.ok;
}

void appendSensorJson(JsonDocument& doc) {
  JsonObject sensor = doc["sensor"].to<JsonObject>();

  sensor["ok"] = sensorState.ok;
  sensor["status"] = sensorState.status;
  sensor["dht_pin"] = DHT_PIN;
  sensor["dht_type"] = DHT_TYPE == 22 ? "DHT22" : "DHT11";
  sensor["last_read_ms"] = sensorState.lastReadMs;
  sensor["fault_message"] = sensorState.faultMessage;

  if (sensorState.ok) {
    sensor["temperature_f"] = sensorState.temperatureF;
    sensor["humidity"] = sensorState.humidity;
  } else {
    sensor["temperature_f"] = nullptr;
    sensor["humidity"] = nullptr;
  }

  // Orion-compatible top-level fields.
  if (sensorState.ok) {
    doc["temp"] = sensorState.temperatureF;
    doc["temperature"] = sensorState.temperatureF;
    doc["current_temp"] = sensorState.temperatureF;
    doc["humidity"] = sensorState.humidity;
    doc["sensor_status"] = "ok";
  } else {
    doc["temp"] = nullptr;
    doc["temperature"] = nullptr;
    doc["current_temp"] = nullptr;
    doc["humidity"] = nullptr;
    doc["sensor_status"] = "fault";
  }
}
