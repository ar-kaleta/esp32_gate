#include "custom_logging.h"
#include <iostream>

#include <Arduino.h>
#include <algorithm> // Include for std::reverse
#include <chrono>    // Add this line to include chrono library
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

void addLogging(std::vector<std::string> &loggingEntries,
                std::string logEntry) {
  // Get current time
  auto now = std::chrono::system_clock::now();
  std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
  std::tm local_time = *std::localtime(&now_time_t);

  // Format time
  std::stringstream ss;
  ss << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");
  std::string formatted_time = ss.str();

  loggingEntries.push_back(formatted_time + " | " + logEntry);
}

std::string formatLogging(std::vector<std::string> loggingEntries) {
  std::string formattedLoggs;

  for (const std::string &entry : loggingEntries) {
    formattedLoggs += entry + "<br>";
  }
  return formattedLoggs;
}

std::vector<std::string>
reverseLogging(std::vector<std::string> loggingEntries) {
  std::reverse(loggingEntries.begin(), loggingEntries.end());
  return loggingEntries;
}

void logEntries(std::vector<std::string> &loggingEntries,
                const std::string &file_path) {
  std::ofstream log_file(file_path, std::ios_base::app);
  if (log_file.is_open()) {
    // Write formatted entries to file
    log_file << formatLogging(loggingEntries);
    log_file.close();
    std::cout << "Entries were logged to file." << std::endl;
  } else {
    std::cerr << "Unable to open log file." << std::endl;
  }
}