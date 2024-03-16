#include <helper.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utils.h>

int main() {
  int isFinished = 0;
  int returnVal = 0;
  int isChild = 0;
  char *filename = NULL;

  while (!isFinished && !isChild) {
    char *line = read_line_from_stdin();
    if (line == NULL) {
      write(1, "Invalid input\n", 14);
      continue;
    }
    char **args = get_args_from_line(line);
    free(line);
    if (args == NULL) {
      write(1, "Invalid args\n", 14);
      continue;
    }
    t_command command = extract_command(args[0]);
    switch (command) {
      case CMD_EXIT:
        isFinished = 1;
        write(1, "Goodbye!\n", 9);
        break;
      case CMD_HELP:
        help_command();
        break;
      case CMD_CREATE:
        returnVal =
            create_file_with_fork(&filename, (const char **)args, &isChild);
        if (!isChild) {
          if (returnVal == 0) {
            write(1, "File created successfully\n", 26);
          } else {
            write(1, "An error occurred\n", 18);
          }
        }
        break;
      case CMD_ADD:
        returnVal =
            add_student_with_fork(filename, (const char **)args, &isChild);
        if (!isChild) {
          if (returnVal == 0) {
            write(1, "Student added successfully\n", 27);
          } else {
            write(1, "An error occurred\n", 18);
          }
        }
        break;
      default:
        write(1, "Invalid command\n", 17);
        break;
    }
    free_args(args);
  }
  if (filename != NULL) free(filename);
  return returnVal;
}