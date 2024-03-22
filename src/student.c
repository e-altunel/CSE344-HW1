#ifndef SRC_STUDENT
#define SRC_STUDENT

#include <debug.h>
#include <stdlib.h>
#include <string_util.h>
#include <student.h>

t_student *student_new(const char *name, const char *grade) {
  t_student *student = (t_student *)calloc(1, sizeof(t_student));
  if (student == NULL) {
    DEBUG_LOG("Failed to allocate memory for student");
    return NULL;
  }
  if (set_name(student, name) == NULL) {
    DEBUG_LOG("Failed to set name for student");
    student_free(student);
    return NULL;
  }
  if (set_grade(student, grade) == NULL) {
    DEBUG_LOG("Failed to set grade for student");
    student_free(student);
    return NULL;
  }
  SUCCESS_LOG("Student created");
  return student;
}
t_student *student_copy(const t_student *student) {
  t_student *new_student = student_new(get_name(student), get_grade(student));
  if (new_student == NULL) {
    DEBUG_LOG("Failed to copy student");
    return NULL;
  }
  SUCCESS_LOG("Student copied");
  return new_student;
}
int student_free(t_student *student) {
  if (student == NULL) {
    DEBUG_LOG("Student is null");
    return EXIT_FAILURE;
  }
  if (student->name != NULL)
    free(student->name);
  if (student->grade != NULL)
    free(student->grade);
  free(student);
  SUCCESS_LOG("Student freed");
  return EXIT_SUCCESS;
}
int student_equal(const t_student *student1, const t_student *student2) {
  if (student1 == NULL || student2 == NULL) {
    DEBUG_LOG("Students is null");
    return -1;
  }
  if (student1->name == NULL || student1->grade == NULL ||
      student2->name == NULL || student2->grade == NULL) {
    DEBUG_LOG("Students features is null");
  }
  if (!strcmp(student1->name, student2->name) &&
      !strcmp(student1->grade, student1->grade)) {
    SUCCESS_LOG("Students are equal");
    return 1;
  }
  SUCCESS_LOG("Students are not equal");
  return 0;
}

int set_name(t_student *student, const char *name) {
  if (student == NULL) {
    DEBUG_LOG("Student is null");
    return EXIT_FAILURE;
  }
  if (student->name != NULL) {
    free(student->name);
    student->name = NULL;
  }
  student->name = string_copy(name);
  if (student->name == NULL) {
    DEBUG_LOG("Failed to set name for student");
    return EXIT_FAILURE;
  }
  SUCCESS_LOG("Name set for student");
  return EXIT_SUCCESS;
}
int set_grade(t_student *student, const char *grade) {
  if (student == NULL) {
    DEBUG_LOG("Student is null");
    return EXIT_FAILURE;
  }
  if (student->grade != NULL) {
    free(student->grade);
    student->grade = NULL;
  }
  student->grade = string_copy(grade);
  if (student->grade == NULL) {
    DEBUG_LOG("Failed to set grade for student");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

char *get_name(const t_student *student) {
  if (student == NULL) {
    DEBUG_LOG("Student is null");
    return NULL;
  }
  return student->name;
}
char *get_grade(const t_student *student) {
  if (student == NULL) {
    DEBUG_LOG("Student is null");
    return NULL;
  }
  return student->grade;
}

#endif /* SRC_STUDENT */
