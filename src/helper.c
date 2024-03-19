#include <stdlib.h>
#include <string.h>

static int isWhitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

int get_argument_length(const char *str) {
  if (str == 0) return -1;
  int length = 0;
  if (str[0] == '"') {
    length++;
    while (str[length] != 0 && str[length] != '"') {
      length++;
    }
    if (str[length] == 0) return -1;
    if (str[length + 1] != 0 && !isWhitespace(str[length + 1])) return -1;
    return length - 1;
  } else {
    int padding = 0;
    while (str[padding] != 0 && isWhitespace(str[padding])) {
      padding++;
    }
    if (str[padding] == 0) return 0;
    while (str[length + padding] != 0 && !isWhitespace(str[length + padding])) {
      length++;
    }
    return length;
  }
}

int get_arguments_count(const char *str) {
  if (str == 0) return -1;
  int count = 0;
  int flag = 1;
  int quote = 0;
  int length = 0;

  while (str[length] != 0) {
    if (isWhitespace(str[length])) {
      if (!quote) {
        flag = 1;
      }
    } else if (quote) {
      if (str[length] == '"') {
        if (str[length + 1] != 0 && !isWhitespace(str[length + 1])) return -1;
        quote = 0;
      }
    } else {
      if (flag) {
        count++;
        flag = 0;
      }
      if (str[length] == '"') {
        if (length > 0 && !isWhitespace(str[length - 1])) return -1;
        quote = 1;
      }
    }
    length++;
  }
  if (quote) return -1;
  return count;
}

char **free_arguments(char **args) {
  if (args == 0) return 0;
  for (int i = 0; args[i] != 0; i++) {
    free(args[i]);
  }
  free(args);
  return 0;
}

char **get_arguments(const char *str) {
  if (str == 0) return 0;
  int count = get_arguments_count(str);
  if (count == -1) return 0;
  char **args = (char **)calloc(count + 1, sizeof(char *));
  if (args == 0) return 0;
  int index = 0;
  int arg_index = 0;
  while (str[index] != 0) {
    while (str[index] != 0 && isWhitespace(str[index])) {
      index++;
    }
    if (str[index] == 0) break;
    int length = get_argument_length(str + index);
    if (length == -1) return free_arguments(args);
    args[arg_index] = (char *)calloc(length + 1, sizeof(char));
    if (args[arg_index] == 0) return free_arguments(args);
    if (str[index] == '"') {
      strncpy(args[arg_index], str + index + 1, length);
      index += length + 2;
    } else {
      strncpy(args[arg_index], str + index, length);
      index += length;
    }
    arg_index++;
  }
  return args;
}
