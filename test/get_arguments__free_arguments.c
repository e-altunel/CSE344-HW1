#include <helper.h>
#include <tester.h>

int main() {
  char **args = 0;
  args = get_arguments("Hello World");
  test_args(args, (char *[]){"Hello", "World", 0},
            "get_arguments(\"Hello World\")");
  test_int(free_arguments(args) == 0, 1, "free_arguments(args) == 0");
  args = get_arguments("Hello World  ");
  test_args(args, (char *[]){"Hello", "World", 0},
            "get_arguments(\"Hello World  \")");
  test_int(free_arguments(args) == 0, 1, "free_arguments(args) == 0");
  args = get_arguments("  Hello World");
  test_args(args, (char *[]){"Hello", "World", 0},
            "get_arguments(\"  Hello World\")");
  test_int(free_arguments(args) == 0, 1, "free_arguments(args) == 0");
  args = get_arguments("  Hello World  ");
  test_args(args, (char *[]){"Hello", "World", 0},
            "get_arguments(\"  Hello World  \")");
  test_int(free_arguments(args) == 0, 1, "free_arguments(args) == 0");
  args = get_arguments("  \"Hello World\"  ");
  test_args(args, (char *[]){"Hello World", 0},
            "get_arguments(\"  \\\"Hello World\\\"  \")");
  test_int(free_arguments(args) == 0, 1, "free_arguments(args) == 0");
  args = get_arguments("  \"Hello World  ");
  test_args(args, 0, "get_arguments(\"  \\\"Hello World  \")");
  test_int(free_arguments(args) == 0, 1, "free_arguments(args) == 0");
  args = get_arguments("  Hello World\"  ");
  test_args(args, 0, "get_arguments(\"  Hello World\\\"  \")");
  test_int(free_arguments(args) == 0, 1, "free_arguments(args) == 0");
  args = get_arguments("  Hello World\"  ");
  test_args(args, 0, "get_arguments(\"  Hello World\\\"  \")");
  test_int(free_arguments(args) == 0, 1, "free_arguments(args) == 0");
}