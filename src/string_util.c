#include <stdlib.h>
#include <string.h>

char *string_copy(const char *string) {
  if (string == NULL) return NULL;
  size_t length = strlen(string);
  char *copy = (char *)calloc(length + 1, sizeof(char));
  if (copy == NULL) return NULL;
  strncpy(copy, string, length);
  return copy;
}