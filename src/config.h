#pragma once

#include <Arduino.h>

static constexpr const char* DEVICE_NAME = "orion-standalone-hvac";
static constexpr const char* FIRMWARE_VERSION = "0.2.0-relay-safety";

static constexpr const char* AP_SSID = "Orion-HVAC-Setup";
static constexpr const char* AP_PASSWORD = "orion12345";

static const IPAddress AP_IP(192, 168, 4, 1);
static const IPAddress AP_GATEWAY(192, 168, 4, 1);
static const IPAddress AP_SUBNET(255, 255, 255, 0);

static constexpr uint8_t STATUS_LED_PIN = 2;

static constexpr uint16_t HTTP_PORT = 80;
static constexpr uint16_t DNS_PORT = 53;

// HVAC relay GPIOs.
// Change these if your board wiring is different.
static constexpr uint8_t RELAY_COOL_STAGE1_PIN = 16;  // Y1
static constexpr uint8_t RELAY_HEAT_STAGE1_PIN = 17;  // W1
static constexpr uint8_t RELAY_FAN_PIN = 18;          // G
static constexpr uint8_t RELAY_COOL_STAGE2_PIN = 19;  // Y2
static constexpr uint8_t RELAY_HEAT_STAGE2_PIN = 21;  // W2

// false = GPIO HIGH turns relay ON.
// true  = GPIO LOW turns relay ON.
static constexpr bool RELAY_ACTIVE_LOW = false;

// Startup holdoff before future control commands are allowed.
static constexpr unsigned long STARTUP_SAFETY_DELAY_MS = 5000;
