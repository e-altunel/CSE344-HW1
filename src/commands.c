#include <fcntl.h>
#include <helper.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void help_command() {
  write(1, "Available commands:\n", 20);
  write(1, "  - exit; to exit the program\n", 30);
  write(1, "  - help; for this message\n", 27);
  write(1, "  - gtuStudentGrades \"<filename>\"; to create a file\n", 52);
  write(1, "  - addStudentGrade \"<student>\" \"<grade>\"; to add a student\n",
        60);
}

/**
 * @brief Extracts the string between the first pair of apostrophes in the given
 * string.
 *
 * @param str The string to extract from.
 * @return char* The extracted string. The caller is responsible for freeing
 * the memory allocated for the string.
 */
static char *get_from_apostrophes(const char *str) {
  if (str == NULL) return NULL;
  while (*str && *str != '"') str++;
  if (*str == '\0') return NULL;
  str++;
  int length = 0;
  while (str[length] && str[length] != '"') length++;
  if (str[length] == '\0') return NULL;
  length++;
  char *result = (char *)malloc(length);
  if (result == NULL) return NULL;
  strncpy(result, str, length - 1);
  result[length - 1] = '\0';
  return result;
}

int create_file_with_fork(char **filename, const char **args, int *isChild) {
  if (args[1] == NULL || args[2] != NULL) {
    write(1, "Invalid arguments, expected: gtuStudentGrades \"<filename>\"\n",
          60);
    return -1;
  }
  if (*filename != NULL) free(*filename);
  *filename = get_from_apostrophes(args[1]);
  if (*filename == NULL) return -1;
  int pid = fork();
  if (pid == -1) {
    free(*filename);
    *filename = NULL;
    return -1;
  }
  if (pid != 0) {
    *isChild = 0;
    int status;
    waitpid(pid, &status, 0);
    return (WIFEXITED(status) && !WEXITSTATUS(status)) ? 0 : -1;
  } else {
    *isChild = 1;
    int fd = open(*filename, O_CREAT, 0644);
    free(*filename);
    *filename = NULL;
    if (fd == -1) {
      return -1;
    }
    close(fd);
    return 0;
  }
}

int add_student_with_fork(const char *filename, const char **args,
                          int *isChild) {
  if (args[1] == NULL || args[2] == NULL || args[3] != NULL) {
    write(1,
          "Invalid arguments, expected: addStudentGrade \"<student>\" "
          "\"<grade>\"\n",
          68);
    return -1;
  }
  if (filename == NULL) {
    write(1,
          "No file created yet, use gtuStudentGrades \"<filename>\" to create "
          "a file\n",
          73);
    return -1;
  }
  char *student_name = get_from_apostrophes(args[1]);
  if (student_name == NULL) {
    write(1, "Invalid student name\n", 21);
    return -1;
  }
  char *grade = get_from_apostrophes(args[2]);
  if (grade == NULL) {
    write(1, "Invalid grade\n", 14);
    free(student_name);
    return -1;
  }
  int pid = fork();
  if (pid == -1) {
    write(1, "Fork failed\n", 12);
    free(student_name);
    free(grade);
    return -1;
  }
  if (pid != 0) {
    *isChild = 0;
    int status;
    waitpid(pid, &status, 0);
    free(student_name);
    free(grade);
    return (WIFEXITED(status) && !WEXITSTATUS(status)) ? 0 : -1;
  } else {
    *isChild = 1;
    int fd = open(filename, O_WRONLY | O_APPEND);
    if (fd == -1) {
      write(1, filename, strlen(filename));
      write(1, "File not found\n", 15);
      free(student_name);
      free(grade);
      return -1;
    }
    write(fd, student_name, strlen(student_name));
    write(fd, ", ", 2);
    write(fd, grade, strlen(grade));
    write(fd, "\n", 1);
    close(fd);
    free(student_name);
    free(grade);
    return 0;
  }
}