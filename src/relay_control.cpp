#include <Arduino.h>

#include "relay_control.h"
#include "config.h"
#include "globals.h"

static RelayState relayState;

static int relayOnLevel() {
  return RELAY_ACTIVE_LOW ? LOW : HIGH;
}

static int relayOffLevel() {
  return RELAY_ACTIVE_LOW ? HIGH : LOW;
}

static void writeRelay(uint8_t pin, bool on) {
  digitalWrite(pin, on ? relayOnLevel() : relayOffLevel());
}

static bool isValidRelayPin(uint8_t pin) {
  // Basic sanity guard for ESP32-S3 GPIO range.
  // This does not validate every board-specific reserved pin,
  // but it catches obviously wrong config.
  return pin <= 48;
}

bool setupRelays() {
  bool ok = true;

  ok = ok && isValidRelayPin(RELAY_COOL_STAGE1_PIN);
  ok = ok && isValidRelayPin(RELAY_COOL_STAGE2_PIN);
  ok = ok && isValidRelayPin(RELAY_HEAT_STAGE1_PIN);
  ok = ok && isValidRelayPin(RELAY_HEAT_STAGE2_PIN);
  ok = ok && isValidRelayPin(RELAY_FAN_PIN);

  pinMode(RELAY_COOL_STAGE1_PIN, OUTPUT);
  pinMode(RELAY_COOL_STAGE2_PIN, OUTPUT);
  pinMode(RELAY_HEAT_STAGE1_PIN, OUTPUT);
  pinMode(RELAY_HEAT_STAGE2_PIN, OUTPUT);
  pinMode(RELAY_FAN_PIN, OUTPUT);

  allRelaysOff(ok ? "boot" : "invalid_relay_pin");

  Serial.println();
  Serial.println("=== HVAC Relays ===");
  Serial.print("Relay config valid: ");
  Serial.println(ok ? "YES" : "NO");
  Serial.print("Active low: ");
  Serial.println(RELAY_ACTIVE_LOW ? "YES" : "NO");
  Serial.print("Y1 GPIO: ");
  Serial.println(RELAY_COOL_STAGE1_PIN);
  Serial.print("Y2 GPIO: ");
  Serial.println(RELAY_COOL_STAGE2_PIN);
  Serial.print("W1 GPIO: ");
  Serial.println(RELAY_HEAT_STAGE1_PIN);
  Serial.print("W2 GPIO: ");
  Serial.println(RELAY_HEAT_STAGE2_PIN);
  Serial.print("G  GPIO: ");
  Serial.println(RELAY_FAN_PIN);

  return ok;
}

void allRelaysOff(const char* reason) {
  relayState.coolStage1 = false;
  relayState.coolStage2 = false;
  relayState.heatStage1 = false;
  relayState.heatStage2 = false;
  relayState.fan = false;

  applyRelayState();

  lastMode = "standby";

  Serial.print("All HVAC relays OFF: ");
  Serial.println(reason);
}

void applyRelayState() {
  writeRelay(RELAY_COOL_STAGE1_PIN, relayState.coolStage1);
  writeRelay(RELAY_COOL_STAGE2_PIN, relayState.coolStage2);
  writeRelay(RELAY_HEAT_STAGE1_PIN, relayState.heatStage1);
  writeRelay(RELAY_HEAT_STAGE2_PIN, relayState.heatStage2);
  writeRelay(RELAY_FAN_PIN, relayState.fan);
}

RelayState getRelayState() {
  return relayState;
}

bool relayAnyActive() {
  return relayState.coolStage1 ||
         relayState.coolStage2 ||
         relayState.heatStage1 ||
         relayState.heatStage2 ||
         relayState.fan;
}

void appendRelayJson(JsonDocument& doc) {
  JsonObject relay = doc["relays"].to<JsonObject>();

  relay["active_low"] = RELAY_ACTIVE_LOW;
  relay["any_active"] = relayAnyActive();

  relay["cool_stage1"] = relayState.coolStage1;
  relay["cool_stage2"] = relayState.coolStage2;
  relay["heat_stage1"] = relayState.heatStage1;
  relay["heat_stage2"] = relayState.heatStage2;
  relay["fan"] = relayState.fan;

  JsonObject pins = relay["pins"].to<JsonObject>();
  pins["cool_stage1"] = RELAY_COOL_STAGE1_PIN;
  pins["cool_stage2"] = RELAY_COOL_STAGE2_PIN;
  pins["heat_stage1"] = RELAY_HEAT_STAGE1_PIN;
  pins["heat_stage2"] = RELAY_HEAT_STAGE2_PIN;
  pins["fan"] = RELAY_FAN_PIN;
}
