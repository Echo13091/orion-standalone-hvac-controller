# Orion Standalone HVAC Controller

Local-first ESP32-S3 HVAC controller.

Built to follow the same architecture style as Orion Standalone Irrigation Controller.

## Goals

- Setup hotspot
- Local web UI
- REST API
- Relay safety layer
- Sensor fault handling
- Persistent configuration
- Optional Wi-Fi onboarding
- No Raspberry Pi required
- No cloud dependency

## Current target

ESP32-S3 with DHT11/DHT22 sensor and HVAC relay outputs:

- Y1 cool stage 1
- Y2 cool stage 2
- W1 heat stage 1
- W2 heat stage 2
- G fan

## Default hotspot

SSID: Orion-HVAC-Setup  
Password: orion12345  
URL: http://192.168.4.1

## Safety model

Initial safety goals:

- All relays off at boot
- Startup safety delay
- Heat/cool changeover lockout
- Minimum compressor runtime
- Minimum compressor off delay
- Sensor fault blocks automatic control
- Manual emergency stop
- One HVAC mode active at a time
