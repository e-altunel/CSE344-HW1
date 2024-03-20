#include <helper.h>
#include <sys/wait.h>
#include <unistd.h>

int gtuStudentGrades(const char *filename) {
  if (filename == 0) return -1;
  int pid = fork();
  if (pid == -1) return -1;
  if (pid != 0) {
    int status;
    waitpid(pid, &status, 0);
    return (WEXITSTATUS(status) == 0) ? 1 : -1;
  }
  return create_file(filename);
}

int addStudentGrade(const char *filename, const char *studentName,
                    const char *grade) {
  if (filename == 0 || studentName == 0 || grade == 0) return -1;
  int pid = fork();
  if (pid == -1) return -1;
  if (pid != 0) {
    int status;
    waitpid(pid, &status, 0);
    return (WEXITSTATUS(status) == 0) ? 1 : -1;
  }
  return append_to_file(filename, studentName, grade);
}
