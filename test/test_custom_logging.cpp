#include "custom_logging.h"
#include <unity.h>

// When running native tests we don't build the project sources. Include the
// implementation file directly so tests can exercise the functions.
#include "../src/custom_logging.cpp"

#include <string>
#include <vector>

void setUp(void) {}
void tearDown(void) {}

void test_format_logging_single(void) {
  std::vector<std::string> entries;
  entries.push_back("action1");
  std::string out = formatLogging(entries);
  TEST_ASSERT_TRUE_MESSAGE(out.find("action1") != std::string::npos,
                           "formatted output must contain original text");
}

void test_format_empty(void) {
  std::vector<std::string> entries;
  std::string out = formatLogging(entries);
  TEST_ASSERT_EQUAL_STRING("", out.c_str());
}

void test_format_multiple(void) {
  std::vector<std::string> entries = {"a", "b", "c"};
  std::string out = formatLogging(entries);
  // Expect each entry separated by <br>
  TEST_ASSERT_TRUE_MESSAGE(out.find("a<br>") != std::string::npos,
                           "a should be present");
  TEST_ASSERT_TRUE_MESSAGE(out.find("b<br>") != std::string::npos,
                           "b should be present");
  TEST_ASSERT_TRUE_MESSAGE(out.find("c<br>") != std::string::npos,
                           "c should be present");
}

void test_reverse_logging(void) {
  std::vector<std::string> entries = {"first", "second", "third"};
  auto rev = reverseLogging(entries);
  TEST_ASSERT_EQUAL_STRING("third", rev[0].c_str());
  TEST_ASSERT_EQUAL_STRING("second", rev[1].c_str());
  TEST_ASSERT_EQUAL_STRING("first", rev[2].c_str());
}

void test_reverse_empty(void) {
  std::vector<std::string> entries;
  auto rev = reverseLogging(entries);
  TEST_ASSERT_EQUAL_INT(0, (int)rev.size());
}

void test_add_logging(void) {
  std::vector<std::string> entries;
  addLogging(entries, "btn_click");
  TEST_ASSERT_TRUE_MESSAGE(entries.size() == 1,
                           "addLogging should append one entry");
  std::string e = entries[0];
  TEST_ASSERT_TRUE_MESSAGE(e.find("btn_click") != std::string::npos,
                           "log entry should contain the message");
}

void test_add_logging_max_entries(void) {
  std::vector<std::string> entries;
  const int TOTAL = 70; // > MAX_LOG_ENTRIES (50) in implementation
  for (int i = 0; i < TOTAL; ++i) {
    addLogging(entries, "msg" + std::to_string(i));
  }
  // Implementation limits to MAX_LOG_ENTRIES (50)
  TEST_ASSERT_TRUE_MESSAGE(entries.size() <= 50,
                           "entries should be capped at 50");
  // Ensure last entry contains the last message
  std::string last = entries.back();
  TEST_ASSERT_TRUE_MESSAGE(last.find("msg" + std::to_string(TOTAL - 1)) !=
                               std::string::npos,
                           "last entry should contain the last message");
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_format_logging_single);
  RUN_TEST(test_format_empty);
  RUN_TEST(test_format_multiple);
  RUN_TEST(test_reverse_logging);
  RUN_TEST(test_reverse_empty);
  RUN_TEST(test_add_logging);
  RUN_TEST(test_add_logging_max_entries);
  return UNITY_END();
}
