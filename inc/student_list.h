#ifndef INC_STUDENT_LIST
#define INC_STUDENT_LIST

#include <student.h>

typedef struct s_student_list {
  t_student **students;
  int size;
  int capacity;
} t_student_list;

t_student_list *student_list_new();
void student_list_free(t_student_list *list);

int student_list_add(t_student_list *list, const t_student *student);
t_student *student_list_get(const t_student_list *list, const int index);
t_student *student_list_remove(t_student_list *list, const int index);

int student_list_find(const t_student_list *list, const t_student *student);
int student_list_find_by_name(const t_student_list *list, const char *name);
int student_list_find_by_grade(const t_student_list *list, const char *grade);

int student_list_resize(t_student_list *list, const int capacity);
#endif /* INC_STUDENT_LIST */
