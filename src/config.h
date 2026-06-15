#pragma once

#include <Arduino.h>

static constexpr const char* DEVICE_NAME = "orion-standalone-hvac";
static constexpr const char* FIRMWARE_VERSION = "0.3.0-sensor-layer";

static constexpr const char* AP_SSID = "Orion-HVAC-Setup";
static constexpr const char* AP_PASSWORD = "orion12345";

static const IPAddress AP_IP(192, 168, 4, 1);
static const IPAddress AP_GATEWAY(192, 168, 4, 1);
static const IPAddress AP_SUBNET(255, 255, 255, 0);

static constexpr uint8_t STATUS_LED_PIN = 2;

static constexpr uint16_t HTTP_PORT = 80;
static constexpr uint16_t DNS_PORT = 53;

// Sensor
static constexpr uint8_t DHT_PIN = 4;
static constexpr uint8_t DHT_TYPE = 11; // 11 = DHT11, 22 = DHT22

static constexpr float MIN_VALID_TEMP_F = 35.0;
static constexpr float MAX_VALID_TEMP_F = 120.0;
static constexpr float MIN_VALID_HUMIDITY = 1.0;
static constexpr float MAX_VALID_HUMIDITY = 100.0;

static constexpr unsigned long SENSOR_READ_INTERVAL_MS = 5000;

// HVAC relay GPIOs.
static constexpr uint8_t RELAY_COOL_STAGE1_PIN = 16;  // Y1
static constexpr uint8_t RELAY_HEAT_STAGE1_PIN = 17;  // W1
static constexpr uint8_t RELAY_FAN_PIN = 18;          // G
static constexpr uint8_t RELAY_COOL_STAGE2_PIN = 19;  // Y2
static constexpr uint8_t RELAY_HEAT_STAGE2_PIN = 21;  // W2

// false = GPIO HIGH turns relay ON.
// true  = GPIO LOW turns relay ON.
static constexpr bool RELAY_ACTIVE_LOW = false;

static constexpr unsigned long STARTUP_SAFETY_DELAY_MS = 5000;
