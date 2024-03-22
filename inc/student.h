#ifndef INC_STUDENT
#define INC_STUDENT

typedef struct s_student {
  char *name;
  char *grade;
} t_student;

t_student *student_new(const char *name, const char *grade);
t_student *student_copy(const t_student *student);
void student_free(t_student *student);

int student_equal(const t_student *student1, const t_student *student2);

int set_name(t_student *student, const char *name);
int set_grade(t_student *student, const char *grade);

char *get_name(const t_student *student);
char *get_grade(const t_student *student);

#endif /* INC_STUDENT */
