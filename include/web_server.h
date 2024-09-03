#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "custom_logging.h"
#include "gpio.h"
#include <WebServer.h>

class MyServer{
public:
  MyServer(int port = 80); // Constructor with a default port
  void handleClient();
  void beginServer();
  void handleRoot();

private:
  WebServer server;
  std::vector<std::string> logging_entries;

  String getPage();
  void handleRequest(String requestPath);
};

#endif // WEB_SERVER_H