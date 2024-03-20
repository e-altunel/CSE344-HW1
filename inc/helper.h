#ifndef INC_HELPER
#define INC_HELPER

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

typedef struct s_student {
  char *name;
  char *grade;
  struct s_student *next;
} t_student;

// Argument Operations
int get_argument_length(const char *str);
int get_arguments_count(const char *str);
char **free_arguments(char **args);
char **get_arguments(const char *str);

// File Operations
int create_file(const char *filename);
char *get_next_line(int fd);
int append_to_file(const char *filename, const char *studentName,
                   const char *grade);
t_student *get_all_students(const char *filename);

// String Operations
char *strjoin(const char *str1, const char *str2);
t_student *extract_student(const char *line);

#endif /* INC_HELPER */
