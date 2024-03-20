#include <fcntl.h>
#include <helper.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int create_file(const char *filename) {
  int fd = open(filename, O_CREAT | O_WRONLY, 0644);
  if (fd == -1) return -1;
  close(fd);
  return 0;
}

static int hasLineBreak(const char *str) {
  if (str == 0) return 0;
  for (int i = 0; str[i] != 0; i++) {
    if (str[i] == '\n') return 1;
  }
  return 0;
}

static char *strdup(const char *str) {
  if (str == 0) return 0;
  int length = strlen(str);
  char *result = (char *)calloc(length + 1, sizeof(char));
  if (result == 0) return 0;
  strcpy(result, str);
  return result;
}

char *get_next_line(int fd) {
  if (fd < 0) return 0;
  char buffer[BUFFER_SIZE + 1];
  char *result = 0;
  char *temp_result = 0;
  int cursor = lseek(fd, 0, SEEK_CUR);
  while (!hasLineBreak(result)) {
    int read_length = read(fd, buffer, BUFFER_SIZE);
    if (read_length == -1) {
      if (result != 0) free(result);
      return 0;
    }
    buffer[read_length] = 0;
    if (read_length == 0) return result;
    temp_result = strjoin(result, buffer);
    if (result != 0) free(result);
    result = temp_result;
  }
  strchr(result, '\n')[0] = 0;
  lseek(fd, cursor + strlen(result) + 1, SEEK_SET);
  return result;
}

char *strjoin(const char *str1, const char *str2) {
  if (str1 == 0 && str2 == 0) return 0;
  if (str1 == 0) return strdup(str2);
  if (str2 == 0) return strdup(str1);
  int length1 = strlen(str1);
  int length2 = strlen(str2);
  char *result = (char *)calloc(length1 + length2 + 1, sizeof(char));
  if (result == 0) return 0;
  strcpy(result, str1);
  strcat(result, str2);
  return result;
}