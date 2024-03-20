extern "C" {
#include <commands.h>
}

#include <fstream>
#include <tester.hpp>

int main() {
  int ret =
      addStudentGrade("test/addStudentGrade.txt", "Emirhan Altunel", "100");
  if (ret == 1) return 0;
  if (ret == -1) {
    test_fail(
        "addStudentGrade(\"test/addStudentGrade.txt\", \"Emirhan Altunel\", "
        "\"100\")");
    return 0;
  }

  std::string line;
  std::fstream file("test/addStudentGrade.txt");
  if (!file.is_open()) {
    test_fail("file does not exist");
    return 0;
  }
  std::getline(file, line);
  test<std::string>(
      line, "\"Emirhan Altunel\";\"100\"",
      "addStudentGrade(\"test/addStudentGrade.txt\", \"Emirhan Altunel\", "
      "\"100\")");
  // remove("test/append_to_file.txt");
}