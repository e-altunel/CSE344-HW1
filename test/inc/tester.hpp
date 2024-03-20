#ifndef TEST_INC_TESTER
#define TEST_INC_TESTER

#include <iostream>
#include <string>
#include <vector>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

static int test_count = 0;

void test_fail(const char *message) {
  test_count++;
  std::cout << "\033[1;31mTest " << test_count << " failed\033[0m: " << message
            << std::endl;
}

void test_pass(const char *message) {
  test_count++;
  std::cout << "\033[1;32mTest " << test_count << " passed\033[0m: " << message
            << std::endl;
}

template <typename T>
void test(T actual, T expected, const char *message) {
  if (actual == expected) {
    test_pass(message);
  } else {
    test_fail(message);
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
      test_fail(message);
      std::cout << "  Expected: " << expected[i] << std::endl;
      std::cout << "  Actual: " << actual[i] << std::endl;
      return;
    }
  }
  if (actual[expected.size()] != nullptr) {
    test_fail(message);
    std::cout << "  Expected: "
              << "nullptr" << std::endl;
    std::cout << "  Actual: " << actual[expected.size()] << std::endl;
    return;
  }
  test_pass(message);
}

#endif /* TEST_INC_TESTER */
