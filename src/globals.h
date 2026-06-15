#pragma once

#include <Arduino.h>
#include <WebServer.h>
#include <DNSServer.h>

extern WebServer server;
extern DNSServer dnsServer;

extern unsigned long bootMillis;
extern String lastMode;
