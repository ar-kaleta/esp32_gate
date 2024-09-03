#include "custom_logging.h"
#include "web_server.h"
#include <Arduino.h>

MyServer myServer(80);

void setup() {
  Serial.begin(921600);
  setupPins();
  setupWifi();
  myServer.beginServer();
}

void loop() {
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
  myServer.handleClient();
}