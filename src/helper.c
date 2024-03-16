#include <define.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int count_args(const char *str) {
  int count = 0;
  int flag = 1;
  while (*str && count < BUFFER_SIZE) {
    if (*str == ' ') {
      flag = 1;
    } else {
      if (flag) {
        count++;
        flag = 0;
      }
    }
    str++;
  }
  return count;
}

int count_arg_length(const char *str) {
  int count = 0;
  while (*str && *str != ' ' && count < BUFFER_SIZE) {
    count++;
    str++;
  }
  return count;
}

void clear_stdin() {
  int c;
  while (read(0, &c, 1) > 0 && c != '\n' && c != -1)
    ;
}

void free_args(char **args) {
  if (args == NULL) return;
  for (int i = 0; args[i] != NULL; i++) {
    free(args[i]);
  }
  free(args);
}