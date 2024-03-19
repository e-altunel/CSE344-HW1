#ifndef TEST_INC_TESTER
#define TEST_INC_TESTER

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// fileno

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

#define PASS(message) printf("\033[1;32m✓ \033[0m");
#define FAIL(message) printf("\n\033[1;31mFAIL\033[0m: %s\n", message);

void test_int(int actual, int expected, const char *message) {
  if (actual == expected) {
    PASS(message);
    fsync(1);
  } else {
    FAIL(message);
    printf("Expected %d, got %d\n", expected, actual);
    fsync(1);
    exit(1);
  }
}

void test_str(const char *actual, const char *expected, const char *message) {
  if (strncmp(actual, expected, BUFFER_SIZE) == 0) {
    PASS(message);
    fsync(1);
  } else {
    FAIL(message);
    printf("Expected \"%s\", got \"%s\"\n", expected, actual);
    fsync(1);
    exit(1);
  }
}

void test_args(char **actual, char **expected, const char *message) {
  int i = 0;
  if (actual == 0 && expected == 0) {
    PASS(message);
    fsync(1);
    return;
  }
  if (actual == 0 || expected == 0) {
    FAIL(message);
    printf("Expected %p, got %p\n",

           (void *)expected, (void *)actual);
    fsync(1);
    exit(1);
  }
  while (actual[i] != 0 && expected[i] != 0) {
    if (strncmp(actual[i], expected[i], BUFFER_SIZE) != 0) {
      FAIL(message);
      printf("Expected \"%s\", got \"%s\"\n", expected[i], actual[i]);
      fsync(1);
      exit(1);
    }
    i++;
  }
  if (actual[i] != 0 || expected[i] != 0) {
    FAIL(message);
    printf("Expected %d arguments, got %d\n", i, i);
    fsync(1);
    exit(1);
  }
  PASS(message);
  fsync(1);
}

#endif /* TEST_INC_TESTER */
