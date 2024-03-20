extern "C" {
#include <commands.h>
}
#include <unistd.h>

#include <tester.hpp>

int main() {
  int ret = gtuStudentGrades("test/gtuStudentGrades.txt");
  if (ret == 1) return 0;
  if (ret == -1) {
    test_fail("gtuStudentGrades(\"test/gtuStudentGrades.txt\")");
    return 0;
  }
  if (access("test/gtuStudentGrades.txt", F_OK) == -1) {
    test_fail("gtuStudentGrades(\"test/gtuStudentGrades.txt\")");
    return 0;
  }
  test_pass("gtuStudentGrades(\"test/gtuStudentGrades.txt\")");
  remove("test/gtuStudentGrades.txt");
}