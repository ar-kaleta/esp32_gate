#ifndef WIFI_H
#define WIFI_H

#include <WiFiMulti.h>

// Wi-Fi credentials should live in `include/secrets.h` which is ignored by
// version control. This file should define `WIFI_SSID` and `WIFI_PASSWORD`.
#include "secrets.h"

// Fallback placeholders (safe defaults for compiling on CI/host).
#ifndef WIFI_SSID
#define WIFI_SSID "your_ssid_here"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "your_password_here"
#endif

void setupWifi();

#endif // WIFI_H
