extern "C" {
#include <helper.h>
}
#include <tester.hpp>

int main() {
  t_student *student;
  student = extract_student("\"Emirhan Altunel\"\"100\"");
  if (student == 0) {
    test_fail("extract_student(\"Emirhan Altunel\"\"100\")");
    return 0;
  }
  test<std::string>(student->name, "Emirhan Altunel",
                    "extract_student(\"Emirhan Altunel\"\"100\")");
  test<std::string>(student->grade, "100",
                    "extract_student(\"Emirhan Altunel\"\"100\")");
  free(student->name);
  free(student->grade);
  free(student);
}