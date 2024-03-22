#ifndef INC_DEBUG
#define INC_DEBUG

#define NULL 0

#ifndef NDEBUG
#define DEBUG_LOG(message)                   \
  {                                          \
    write(1, "\033[31m[DEBUG]\033[0m ", 18); \
    write(1, __FILE__, strlen(__FILE__));    \
    write(1, ":", 1);                        \
    write(1, __LINE__, strlen(__LINE__));    \
    write(1, " ", 1);                        \
    write(1, message, strlen(message));      \
    write(1, "\n", 1);                       \
  }
#define SUCCESS_LOG(message)                   \
  {                                            \
    write(1, "\033[32m[SUCCESS]\033[0m ", 20); \
    write(1, __FILE__, strlen(__FILE__));      \
    write(1, ":", 1);                          \
    write(1, __LINE__, strlen(__LINE__));      \
    write(1, " ", 1);                          \
    write(1, message, strlen(message));        \
    write(1, "\n", 1);                         \
  }
#else
#define DEBUG_LOG(message)
#define SUCCESS_LOG(message)
#endif

#endif /* INC_DEBUG */
