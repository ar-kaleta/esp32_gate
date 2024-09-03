#include "wifi.h"


void setupWifi() {
  WiFiMulti wifiMulti;

  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  Serial.println("Connected");
  Serial.println(WiFi.localIP());
}