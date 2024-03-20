extern "C" {
#include <helper.h>
}
#include <tester.hpp>

int main() {
  char **args = 0;
  args = get_arguments("Hello World");
  std::vector<std::string> expected = {"Hello", "World"};
  test(args, expected, "get_arguments(\"Hello World\")");
  free_arguments(args);

  args = get_arguments("Hello World  ");
  test(args, expected, "get_arguments(\"Hello World  \")");
  free_arguments(args);

  args = get_arguments("  Hello World");
  test(args, expected, "get_arguments(\"  Hello World\")");
  free_arguments(args);

  args = get_arguments("  Hello World  ");
  test(args, expected, "get_arguments(\"  Hello World  \")");
  free_arguments(args);

  args = get_arguments("  \"Hello World\"  ");
  std::vector<std::string> expected2 = {"Hello World"};
  test(args, expected2, "get_arguments(\"  \\\"Hello World\\\"  \")");
  free_arguments(args);

  args = get_arguments("  \"Hello World  ");
  test<void *>(args, nullptr, "get_arguments(\"  \\\"Hello World  \")");
  free_arguments(args);

  args = get_arguments("  Hello World\"  ");
  test<void *>(args, nullptr, "get_arguments(\"  Hello World\\\"  \")");
  free_arguments(args);

  args = get_arguments("  Hello World\"  ");
  test<void *>(args, nullptr, "get_arguments(\"  Hello World\\\"  \")");
  free_arguments(args);
}