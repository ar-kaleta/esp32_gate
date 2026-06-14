#include "wifi.h"
#include <time.h>

void setupWifi() {
  WiFiMulti wifiMulti;

  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  Serial.println("Connected");
  Serial.println(WiFi.localIP());

  // Configure NTP time synchronization so logs have correct timestamps
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("Waiting for time sync...");
  time_t now = time(nullptr);
  int retry = 0;
  const int maxRetries = 20;
  while (now < 8 && retry < maxRetries) {
    delay(500);
    now = time(nullptr);
    retry++;
  }
  if (now >= 8) {
    struct tm timeinfo;
    localtime_r(&now, &timeinfo);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
    Serial.print("Time synchronized: ");
    Serial.println(buf);
  } else {
    Serial.println("Time sync failed or timed out");
  }
}