#pragma once

#include <Arduino.h>

static constexpr const char* DEVICE_NAME = "orion-standalone-hvac";
static constexpr const char* FIRMWARE_VERSION = "0.1.0-hotspot";

static constexpr const char* AP_SSID = "Orion-HVAC-Setup";
static constexpr const char* AP_PASSWORD = "orion12345";

static const IPAddress AP_IP(192, 168, 4, 1);
static const IPAddress AP_GATEWAY(192, 168, 4, 1);
static const IPAddress AP_SUBNET(255, 255, 255, 0);

static constexpr uint8_t STATUS_LED_PIN = 2;

static constexpr uint16_t HTTP_PORT = 80;
static constexpr uint16_t DNS_PORT = 53;
