#include <define.h>
#include <fcntl.h>
#include <helper.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utils.h>

char *read_line_from_stdin() {
  (void)!write(1, "Enter a line: ", 14);
  fsync(1);
  char *buffer = (char *)malloc(BUFFER_SIZE + 1);
  if (buffer == NULL) {
    return NULL;
  }
  int bytes_read = read(0, buffer, BUFFER_SIZE);
  if (bytes_read == -1 || bytes_read == 0 || bytes_read == BUFFER_SIZE) {
    free(buffer);
    clear_stdin();
    DEBUG_LOG(NULL, "Invalid input\n");
  } else {
    buffer[bytes_read] = '\0';
    if (buffer[bytes_read - 1] == '\n') {
      buffer[bytes_read - 1] = '\0';
    }
    return buffer;
  }
}

char **get_args_from_line(const char *line) {
  if (line == NULL) DEBUG_LOG(NULL, "Line is NULL\n");
  int count = count_args(line);
  if (count == 0 || count == -1) DEBUG_LOG(NULL, "Invalid count\n");
  char **args = (char **)malloc((count + 1) * sizeof(char *));
  if (args == NULL) DEBUG_LOG(NULL, "Memory allocation failed\n");
  while (*line && *line == ' ') line++;
  for (int i = 0; i < count; i++) {
    int length = count_arg_length(line);
    if (length == -1) {
      for (int j = 0; j < i; j++) {
        free(args[j]);
      }
      free(args);
      DEBUG_LOG(NULL, "Invalid length\n");
    }
    if (*line == '\"') {
      line++;
    }
    args[i] = (char *)malloc(length + 1);
    if (args[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(args[j]);
      }
      free(args);
      DEBUG_LOG(NULL, "Memory allocation failed\n");
    }
    strncpy(args[i], line, length);
    args[i][length] = '\0';
    line += length;
    while (*line && *line == ' ') line++;
  }
  args[count] = NULL;
  return args;
}

t_command extract_command(const char *line) {
  if (line == NULL) return CMD_INVALID;
  if (strncmp(line, "exit", 4) == 0) return CMD_EXIT;
  if (strncmp(line, "help", 4) == 0) return CMD_HELP;
  if (strncmp(line, "gtuStudentGrades", 6) == 0) return CMD_CREATE;
  if (strncmp(line, "addStudentGrade", 4) == 0) return CMD_ADD;
  return CMD_INVALID;
}
