#include "custom_logging.h"
#include "gpio.h"
#include <Arduino.h>
#include <WebServer.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;
WebServer server(80);

#define WIFI_SSID "UPC4555938"
#define WIFI_PASSWORD "pttwatKejQw6"

int LEDPIN = 32;

std::vector<std::string> logging_entries;

/////////////////////////

String getPage(std::vector<std::string> logging_entries) {

  std::string formattedLogs = formatLogging(logging_entries);

  for (const std::string &entry : logging_entries) {
    Serial.println(String(entry.c_str()));
  }

  String page = R"(
    <!DOCTYPE html>
    <html>
    <head>
        <title>Gate</title>
    </head>
    <center><b>
    <table><tr>
        <td><form action="./first_on">
            <input type="submit" value="1 ON" style="height:120px; width:120px" />
        </form></td>
        <td><form action="./second_on">
            <input type="submit" value="2 ON" style="height:120px; width:120px" />
        </form></td>
    </tr></table>
    <table><tr>
        <td><form action="./first_off">
            <input type="submit" value="1 OFF" style="height:120px; width:120px" />
        </form></td>
        <td><form action="./second_off">
            <input type="submit" value="2 OFF" style="height:120px; width:120px" />
        </form></td>
    </tr></table>
    <h1 align="left">)" +
                String(formattedLogs.c_str()) + R"(</h1></body></html>)";
  return page;
}

void handleRequest(String requestPath,
                   std::vector<std::string> &logging_entries) {

  if (requestPath.startsWith("/first_on")) {
    addLogging(logging_entries, firstOn());
  }

  if (requestPath.startsWith("/first_off")) {

    addLogging(logging_entries, firstOff());
  }

  if (requestPath.startsWith("/second_on")) {

    addLogging(logging_entries, secondOn());
  }

  if (requestPath.startsWith("/second_off")) {

    addLogging(logging_entries, secondOff());
  }
}

void handleRoot() {
  handleRequest(server.uri(), logging_entries);

  server.send(200, "text/html", getPage(reverseLogging(logging_entries)));
}

void beginServer() {
  
  server.on("/", handleRoot);
  server.on("/first_on", handleRoot);
  server.on("/first_off", handleRoot);
  server.on("/second_on", handleRoot);
  server.on("/second_off", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

//////////////////////

void setup() {
  Serial.begin(921600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(GPIO_NUM_4, OUTPUT);
  pinMode(GPIO_NUM_5, OUTPUT);

  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  Serial.println("Connected");
  Serial.println(WiFi.localIP());

  beginServer();
}

void loop() {
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);

  server.handleClient();
}