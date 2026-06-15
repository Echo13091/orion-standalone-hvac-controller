#include "globals.h"
#include "config.h"

WebServer server(HTTP_PORT);
DNSServer dnsServer;

unsigned long bootMillis = 0;
String lastMode = "booting";
