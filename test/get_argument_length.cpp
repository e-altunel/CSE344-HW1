extern "C" {
#include <helper.h>
}

#include <tester.hpp>

int main() {
  test(get_argument_length(0), -1, "get_argument_length(0) == -1");
  test(get_argument_length(""), 0, "get_argument_length(\"\") == 0");
  test(get_argument_length("Hello"), 5, "get_argument_length(\"Hello\") == 5");
  test(get_argument_length("Hello World"), 5,
       "get_argument_length(\"Hello World\") == 5");
  test(get_argument_length("\"Hello World\""), 11,
       "get_argument_length(\"\\\"Hello World\\\"\") == 11");
  test(get_argument_length("\"Hello World"), -1,
       "get_argument_length(\"\\\"Hello World\") == -1");
  test(get_argument_length("Hello World\""), 5,
       "get_argument_length(\"Hello World\\\"\") == 5");
  test(get_argument_length("\"Hello World\" "), 11,
       "get_argument_length(\"\\\"Hello World\\\" \") == 11");
  test(get_argument_length("\"Hello World\"more"), -1,
       "get_argument_length(\"\\\"Hello World\\\"more\") == -1");
  test(get_argument_length("         Hello"), 5,
       "get_argument_length(\"         Hello\") == 5");
  return 0;
}