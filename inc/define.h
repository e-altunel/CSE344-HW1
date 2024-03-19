#ifndef INC_DEFINE
#define INC_DEFINE

#ifndef NULL
#define NULL 0
#endif
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

#ifndef DEBUG_LOG
#ifndef NDEBUG
#include <stdio.h>
#define DEBUG_LOG(returnVal, ...)                                       \
  {                                                                     \
    printf("\033[31m[DEBUG]\033[0m %20s:%-3d -> ", __FILE__, __LINE__); \
    printf(__VA_ARGS__);                                                \
    return returnVal;                                                   \
  }
#else
#define DEBUG_LOG(returnVal, ...) return returnVal;
#endif
#endif

#ifndef INFO_LOG
#ifndef NDEBUG
#include <stdio.h>
#define INFO_LOG(...)                                                  \
  {                                                                    \
    printf("\033[32m[INFO]\033[0m %20s:%-3d -> ", __FILE__, __LINE__); \
    printf(__VA_ARGS__);                                               \
  }
#else
#define INFO_LOG(...) ;
#endif
#endif

#endif /* INC_DEFINE */