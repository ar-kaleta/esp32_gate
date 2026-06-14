#include "custom_logging.h"

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <iostream>
#endif
#include <algorithm>
#include <ctime>
#include <string>
#include <vector>

void addLogging(std::vector<std::string> &loggingEntries,
                const std::string &logEntry) {
  time_t now = time(nullptr);
  struct tm timeinfo;
#if defined(ARDUINO_ARCH_ESP32)
  localtime_r(&now, &timeinfo);
#else
  localtime_r(&now, &timeinfo);
#endif

  char buf[32];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);

  loggingEntries.push_back(std::string(buf) + " | " + logEntry);

  // Keep logs bounded to avoid unbounded memory growth on embedded device
  const size_t MAX_LOG_ENTRIES = 50;
  if (loggingEntries.size() > MAX_LOG_ENTRIES) {
    size_t removeCount = loggingEntries.size() - MAX_LOG_ENTRIES;
    loggingEntries.erase(loggingEntries.begin(),
                         loggingEntries.begin() + removeCount);
  }
}

std::string formatLogging(const std::vector<std::string> &loggingEntries) {
  std::string formatted;
  for (const auto &e : loggingEntries) {
    formatted += e + "<br>";
  }
  return formatted;
}

std::vector<std::string>
reverseLogging(const std::vector<std::string> &loggingEntries) {
  std::vector<std::string> copy = loggingEntries;
  std::reverse(copy.begin(), copy.end());
  return copy;
}

void logEntries(const std::vector<std::string> &loggingEntries,
                const std::string &file_path) {
  // File I/O may not be available on all builds. Print to Serial (embedded)
  // or std::cout (native host) instead.
#if defined(ARDUINO)
  Serial.println("--- Log entries (would write to: " +
                 String(file_path.c_str()) + ") ---");
  for (const auto &e : loggingEntries) {
    Serial.println(String(e.c_str()));
  }
#else
  std::cout << "--- Log entries (would write to: " << file_path << ") ---\n";
  for (const auto &e : loggingEntries) {
    std::cout << e << std::endl;
  }
#endif
}