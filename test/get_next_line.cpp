extern "C" {
#include <helper.h>
}
#include <fcntl.h>
#include <unistd.h>

#include <fstream>
#include <tester.hpp>

int main() {
  std::fstream file;
  file.open("test/get_next_line.txt", std::ios::out);
  file << "Hello World 1\n";
  file << "Hello World 2\n";
  file << "Hello World 3\n";
  file << "Hello World 4\n";
  file << "Hello World 5\n";
  file.close();

  int fd = open("test/get_next_line.txt", O_RDONLY);
  const char *line = 0;

  line = get_next_line(fd);
  test(line, "Hello World 1", "get_next_line(fd)");
  free((void *)line);

  line = get_next_line(fd);
  test(line, "Hello World 2", "get_next_line(fd)");
  free((void *)line);

  line = get_next_line(fd);
  test(line, "Hello World 3", "get_next_line(fd)");
  free((void *)line);

  line = get_next_line(fd);
  test(line, "Hello World 4", "get_next_line(fd)");
  free((void *)line);

  line = get_next_line(fd);
  test(line, "Hello World 5", "get_next_line(fd)");
  free((void *)line);

  line = get_next_line(fd);
  test<void *>((void *)line, nullptr, "get_next_line(fd)");
  free((void *)line);

  close(fd);
  remove("test/get_next_line.txt");
}