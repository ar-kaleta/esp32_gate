#include "web_server.h"

// Constructor
MyServer::MyServer(int port) : server(port) {
  // Initialize logging entries or any other setup
  logging_entries = {};
}

void MyServer::handleClient() {
    server.handleClient();
}

// Method to begin the server and register routes
void MyServer::beginServer() {
    server.on("/", [this]() { handleRoot(); });
    server.on("/first_on", [this]() { handleRoot(); });
    server.on("/first_off", [this]() { handleRoot(); });
    server.on("/second_on", [this]() { handleRoot(); });
    server.on("/second_off", [this]() { handleRoot(); });

    server.begin();
    Serial.println("HTTP server started");
}

// Root handler method
void MyServer::handleRoot() {
  handleRequest(server.uri());
  server.send(200, "text/html", getPage());
}

// Method to handle HTTP requests
void MyServer::handleRequest(String requestPath) {
  if (requestPath.startsWith("/first_on")) {
    addLogging(logging_entries, firstOn());
  } 
  else if (requestPath.startsWith("/first_off")) {
    addLogging(logging_entries, firstOff());
  } 
  else if (requestPath.startsWith("/second_on")) {
    addLogging(logging_entries, secondOn());
  } 
  else if (requestPath.startsWith("/second_off")) {
    addLogging(logging_entries, secondOff());
  }
}

// Method to generate the HTML page
String MyServer::getPage() {
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
