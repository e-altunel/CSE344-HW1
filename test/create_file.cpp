extern "C" {
#include <helper.h>
}
#include <fcntl.h>
#include <unistd.h>

#include <tester.hpp>

int main() {
  create_file("test/create_file.txt");
  if (access("test/create_file.txt", F_OK) == -1)
    test_fail("create_file(\"test/create_file.txt\")");
  else
    test_pass("create_file(\"test/create_file.txt\")");

  remove("test/create_file.txt");
}