#include "web_server.h"

// Constructor
MyServer::MyServer(int port) : server(port) {
  // Initialize logging entries or any other setup
  logging_entries = {};
}

void MyServer::handleClient(std::string log) {
  if (log != "") {
    addLogging(logging_entries, log);
  }
  server.handleClient();
}

// Method to begin the server and register routes
void MyServer::beginServer() {
  server.on("/", [this]() { handleRoot(); });
  server.on("/first_on", [this]() { handleRoot(); });
  server.on("/first_off", [this]() { handleRoot(); });
  server.on("/second_on", [this]() { handleRoot(); });
  server.on("/second_off", [this]() { handleRoot(); });

  // New route for getting the current pin status
  server.on("/get_status", [this]() { handleStatus(); });

  server.begin();
  Serial.println("HTTP server started");
}

// Root handler method
void MyServer::handleRoot() {
  handleRequest(server.uri());
  server.send(200, "text/html", getPage());
}

void MyServer::handleStatus() {
  // Get the current states of the pins
  String status =
      "GPIO 4: " + String(digitalRead(GPIO_NUM_4) == HIGH ? "ON" : "OFF") +
      ", GPIO 5: " + String(digitalRead(GPIO_NUM_5) == HIGH ? "ON" : "OFF");

  // Send the response to the client
  server.send(200, "text/plain", status);
}

// Method to handle HTTP requests
void MyServer::handleRequest(String requestPath) {
  if (requestPath.startsWith("/first_on")) {
    addLogging(logging_entries, firstOn());
  } else if (requestPath.startsWith("/first_off")) {
    addLogging(logging_entries, firstOff());
  } else if (requestPath.startsWith("/second_on")) {
    addLogging(logging_entries, secondOn());
  } else if (requestPath.startsWith("/second_off")) {
    addLogging(logging_entries, secondOff());
  }
}

// Method to generate the HTML page
String MyServer::getPage() {
  std::string formattedLogs = formatLogging(logging_entries);

  // Serial output of logs
  for (const std::string &entry : logging_entries) {
    Serial.println(String(entry.c_str()));
  }

  // HTML page with JavaScript to poll server for pin status updates
  String page = R"(
    <!DOCTYPE html>
    <html>
    <head>
        <title>Gate</title>
        <script>
            // Function to update the pin status every 2 seconds
            function updateStatus() {
                fetch('/get_status')
                .then(response => response.text())
                .then(status => {
                    document.getElementById("status").innerHTML = status;
                });
            }

            setInterval(updateStatus, 2000);  // Update every 2 seconds
        </script>
    </head>
    <body>
    <center><b>
    <!-- GPIO Status -->
    <h2>GPIO Pin Status:</h2>
    <p id="status">Waiting for update...</p>
    <br>

    <!-- Form buttons for pin actions -->
    <table><tr>
        <td><form action="./first_on">
            <input type="submit" value="GPIO 4 ON" style="height:120px; width:120px" />
        </form></td>
        <td><form action="./second_on">
            <input type="submit" value="GPIO 5 ON" style="height:120px; width:120px" />
        </form></td>
    </tr></table>
    <table><tr>
        <td><form action="./first_off">
            <input type="submit" value="GPIO 4 OFF" style="height:120px; width:120px" />
        </form></td>
        <td><form action="./second_off">
            <input type="submit" value="GPIO 5 OFF" style="height:120px; width:120px" />
        </form></td>
    </tr></table>
    
    <!-- Logs Section -->
    <h2>Action Logs:</h2>
    <h1 align="left">)" +
                String(formattedLogs.c_str()) + R"(</h1>
    </body></html>)";

  return page;
}
