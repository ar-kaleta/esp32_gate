#ifndef CUSTOM_LOGGING_H
#define CUSTOM_LOGGING_H

#include <string>
#include <vector>

void addLogging(std::vector<std::string> &loggingEntries, std::string logEntry);
std::string formatLogging(std::vector<std::string> loggingEntries);
std::vector<std::string>
reverseLogging(std::vector<std::string> loggingEntries);
void logEntries(std::vector<std::string> &loggingEntries,
                const std::string &file_path);

#endif // CUSTOM_LOGGING_H