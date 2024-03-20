#ifndef TEST_INC_TESTER
#define TEST_INC_TESTER

#include <iostream>
#include <string>
#include <vector>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

static int test_count = 0;

template <typename T>
void test(T actual, T expected, const char *message) {
  test_count++;
  if (actual == expected) {
    std::cout << "Test " << test_count << " passed: " << message << std::endl;
  } else {
    std::cout << "Test " << test_count << " failed: " << message << std::endl;
    std::cout << "  Expected: " << expected << std::endl;
    std::cout << "  Actual: " << actual << std::endl;
  }
}

template <>
void test<const char *>(const char *actual, const char *expected,
                        const char *message) {
  test(std::string(actual), std::string(expected), message);
}

void test(char **actual, std::vector<std::string> expected,
          const char *message) {
  test_count++;
  for (std::size_t i = 0; i < expected.size(); i++) {
    if (actual[i] != expected[i]) {
      std::cout << "Test " << test_count << " failed: " << message << std::endl;
      std::cout << "  Expected: " << expected[i] << std::endl;
      std::cout << "  Actual: " << actual[i] << std::endl;
      return;
    }
  }
  if (actual[expected.size()] != nullptr) {
    std::cout << "Test " << test_count << " failed: " << message << std::endl;
    std::cout << "  Expected: "
              << "nullptr" << std::endl;
    std::cout << "  Actual: " << actual[expected.size()] << std::endl;
    return;
  }
  std::cout << "Test " << test_count << " passed: " << message << std::endl;
}

#endif /* TEST_INC_TESTER */
