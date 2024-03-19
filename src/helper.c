#include <define.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int isWhitespace(char c) { return (c == ' ' || c == '\n' || c == '\0'); }

int count_args(const char *str) {
  int count = 0;
  int flag = 1;
  int quote_flag = 0;
  while (*str && count < BUFFER_SIZE) {
    if (!quote_flag && *str == ' ') {
      flag = 1;
    } else {
      if (!quote_flag && *str == '\"')
        quote_flag = 1;
      else if (quote_flag && *str == '\"') {
        if (!isWhitespace(*(str + 1))) DEBUG_LOG(-1, "Invalid quote\n");
        quote_flag = 0;
      }
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
  if (*str == '\"') {
    str++;
    while (*str && *str != '\"' && count < BUFFER_SIZE) {
      count++;
      str++;
    }
    if (count == BUFFER_SIZE) DEBUG_LOG(-1, "Buffer overflow\n");
    if (*str != '\"') DEBUG_LOG(-1, "Quote not closed\n");
    if (!isWhitespace(*(str + 1)))
      DEBUG_LOG(-1, "Quote has invalid character after it\n");
    return count;
  } else {
    while (*str && *str != ' ' && count < BUFFER_SIZE) {
      if (*str == '\"') DEBUG_LOG(-1, "Invalid quote\n");
      count++;
      str++;
    }
    if (count == BUFFER_SIZE) DEBUG_LOG(-1, "Buffer overflow\n");
    return count;
  }
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