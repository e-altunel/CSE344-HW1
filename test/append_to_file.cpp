extern "C" {
#include <helper.h>
}
#include <fcntl.h>
#include <unistd.h>

#include <fstream>
#include <tester.hpp>

int main() {
  int fd = open("test/append_to_file.txt", O_CREAT | O_RDWR, 0644);
  if (fd == -1) {
    test_fail("open(\"test/append_to_file.txt\", O_CREAT | O_RDWR, 0644)");
    return 0;
  }
  test(append_to_file("test/append_to_file.txt", "Hello, World!", "Deneme"), 0,
       "append_to_file(\"test/append_to_file.txt\", \"Hello, World!\", "
       "\"Deneme\")");
  test(append_to_file("test/append_to_file.txt", "Hello, World!", 0), -1,
       "append_to_file(\"test/append_to_file.txt\", \"Hello, World!\", 0)");
  test(append_to_file("test/append_to_file.txt", 0, "Deneme"), -1,
       "append_to_file(\"test/append_to_file.txt\", 0, \"Deneme\")");
  test(append_to_file(0, "Hello, World!", "Deneme"), -1,
       "append_to_file(0, \"Hello, World!\", \"Deneme\")");
  test(append_to_file("test/append_to_file.txt", "Emirhan Altunel", "100"), 0,
       "append_to_file(\"test/append_to_file.txt\", \"Emirhan Altunel\", "
       "\"100\")");
  if (access("test/append_to_file.txt", F_OK) == -1) {
    test_fail("file does not exist");
    return 0;
  }
  std::fstream file("test/append_to_file.txt");
  std::string line;
  std::getline(file, line);
  test<std::string>(
      line, "\"Hello, World!\"\"Deneme\"",
      "append_to_file(\"test/append_to_file.txt\", \"Hello, World!\", "
      "\"Deneme\")");
  std::getline(file, line);
  test<std::string>(
      line, "\"Emirhan Altunel\"\"100\"",
      "append_to_file(\"test/append_to_file.txt\", \"Emirhan Altunel\", "
      "\"100\")");
  remove("test/append_to_file.txt");
}