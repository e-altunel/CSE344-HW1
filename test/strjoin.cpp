extern "C" {
#include <helper.h>
}
#include <tester.hpp>

int main() {
  char *str = strjoin("Hello", "World");
  test<const char *>(str, "HelloWorld", "strjoin(\"Hello\", \"World\")");
  free(str);

  str = strjoin("Hello", 0);
  test<const char *>(str, "Hello", "strjoin(\"Hello\", 0)");
  free(str);

  str = strjoin(0, "World");
  test<const char *>(str, "World", "strjoin(0, \"World\")");
  free(str);

  str = strjoin(0, 0);
  test<void *>((void *)str, 0, "strjoin(0, 0)");
}