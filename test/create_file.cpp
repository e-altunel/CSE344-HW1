extern "C" {
#include <helper.h>
}
#include <fcntl.h>
#include <unistd.h>

#include <tester.hpp>

int main() {
  create_file("test/create_file.txt");
  if (access("test/create_file.txt", F_OK) == -1) {
    std::cout << "Test 1 failed: create_file(\"test/create_file.txt\")"
              << std::endl;
  } else {
    std::cout << "Test 1 passed: create_file(\"test/create_file.txt\")"
              << std::endl;
  }
  remove("test/create_file.txt");
}