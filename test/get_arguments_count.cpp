extern "C" {
#include <helper.h>
}

#include <tester.hpp>

int main() {
  test(get_arguments_count(0), -1, "get_arguments_count(0) == -1");
  test(get_arguments_count(""), 0, "get_arguments_count(\"\") == 0");
  test(get_arguments_count("Hello"), 1, "get_arguments_count(\"Hello\") == 1");
  test(get_arguments_count("Hello World"), 2,
       "get_arguments_count(\"Hello World\") == 2");
  test(get_arguments_count("\"Hello World\""), 1,
       "get_arguments_count(\"\\\"Hello World\\\"\") == 1");
  test(get_arguments_count("Hello\"World"), -1,
       "get_arguments_count(\"Hello\\\"World\") == -1");
  test(get_arguments_count("Hello \"World"), -1,
       "get_arguments_count(\"Hello \\\"World\") == -1");
  test(get_arguments_count("Hello\" World"), -1,
       "get_arguments_count(\"Hello\\\" World\") == -1");
  test(get_arguments_count("Hello \"World\""), 2,
       "get_arguments_count(\"Hello \\\"World\\\"\") == 2");
  test(get_arguments_count("Hello \"World Emirhan\" "), 2,
       "get_arguments_count(\"Hello \\\"World Emirhan\\\" \") == 2");
  test(get_arguments_count("Hello \"World\"Emirhan "), -1,
       "get_arguments_count(\"Hello \\\"World\\\"Emirhan \") == -1");
}