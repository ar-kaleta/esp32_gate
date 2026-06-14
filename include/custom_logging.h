#ifndef CUSTOM_LOGGING_H
#define CUSTOM_LOGGING_H

#include <string>
#include <vector>

void addLogging(std::vector<std::string> &loggingEntries,
                const std::string &logEntry);
std::string formatLogging(const std::vector<std::string> &loggingEntries);
std::vector<std::string>
reverseLogging(const std::vector<std::string> &loggingEntries);
// Note: on embedded devices file I/O may not be available; this function
// currently prints entries to Serial. Keep signature const-ref for safety.
void logEntries(const std::vector<std::string> &loggingEntries,
                const std::string &file_path);

#endif // CUSTOM_LOGGING_H