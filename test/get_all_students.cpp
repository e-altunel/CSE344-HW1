extern "C" {
#include <helper.h>
}

#include <fstream>
#include <tester.hpp>

static void free_students(t_student *student) {
  if (student == 0) return;
  free_students(student->next);
  if (student->name != 0) free(student->name);
  if (student->grade != 0) free(student->grade);
  free(student);
}

int main() {
  std::ofstream file("test/get_all_students.txt");
  if (!file.is_open()) {
    test_fail("file does not exist");
    return 0;
  }
  file << "\"Emirhan Altunel\"\"100\"\n";
  file << "\"Hasan Karakuş\"\"99\"\n";
  file << "\"Hüseyin Koçak\"\"98\"\n";
  file.close();

  t_student *students = get_all_students("test/get_all_students.txt");
  if (students == 0) {
    test_fail("get_all_students(\"test/get_all_students.txt\")");
    return 0;
  }
  t_student *current = students;
  test<std::string>(current->name, "Emirhan Altunel",
                    "get_all_students(\"test/get_all_students.txt\")");
  test<std::string>(current->grade, "100",
                    "get_all_students(\"test/get_all_students.txt\")");
  current = current->next;
  test<std::string>(current->name, "Hasan Karakuş",
                    "get_all_students(\"test/get_all_students.txt\")");
  test<std::string>(current->grade, "99",
                    "get_all_students(\"test/get_all_students.txt\")");
  current = current->next;
  test<std::string>(current->name, "Hüseyin Koçak",
                    "get_all_students(\"test/get_all_students.txt\")");
  test<std::string>(current->grade, "98",
                    "get_all_students(\"test/get_all_students.txt\")");

  free_students(students);
  remove("test/get_all_students.txt");
}