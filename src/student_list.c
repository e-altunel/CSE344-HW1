#ifndef SRC_STUDENT_LIST
#define SRC_STUDENT_LIST

#include <debug.h>
#include <stdlib.h>
#include <student_list.h>

t_student_list *student_list_new() {
  t_student_list *list = (t_student_list *)calloc(1, sizeof(t_student_list));
  if (list == NULL) {
    DEBUG_LOG("Failed to allocate memory for students");
    return NULL;
  }
  list->size = 0;
  list->capacity = 10;
  list->students = (t_student **)calloc(list->capacity, sizeof(t_student *));
  if (list->students == NULL) {
    DEBUG_LOG("Failed to allocate memory for students");
    student_list_free(list);
    return NULL;
  }
  SUCCESS_LOG("Student list created");
  return list;
}
void student_list_free(t_student_list *list) {
  if (list == NULL) {
    DEBUG_LOG("Student list is null");
    return;
  }
  for (int i = 0; i < list->size; i++) {
    student_free(list->students[i]);
  }
  free(list->students);
  free(list);
  SUCCESS_LOG("Student list freed");
}

int student_list_add(t_student_list *list, const t_student *student) {
  if (list == NULL) {
    DEBUG_LOG("Student list is null");
    return EXIT_FAILURE;
  }
  if (student == NULL) {
    DEBUG_LOG("Student is null");
    return EXIT_FAILURE;
  }
  if (list->size == list->capacity) {
    if (student_list_resize(list, list->capacity * 2) == EXIT_FAILURE) {
      DEBUG_LOG("Failed to resize student list");
      return EXIT_FAILURE;
    }
  }
  list->students[list->size] = student_copy(student);
  if (list->students[list->size] == NULL) {
    DEBUG_LOG("Failed to copy student");
    return EXIT_FAILURE;
  }
  list->size++;
  SUCCESS_LOG("Student added");
  return EXIT_SUCCESS;
}
t_student *student_list_get(const t_student_list *list, const int index) {
  if (list == NULL) {
    DEBUG_LOG("Student list is null");
    return NULL;
  }
  if (index < 0 || index >= list->size) {
    DEBUG_LOG("Index is invalid.");
    return NULL;
  }
  return list->students[index];
}
t_student *student_list_remove(t_student_list *list, const int index) {
  if (list == NULL) {
    DEBUG_LOG("Student list is null");
    return NULL;
  }
  if (index < 0 || index >= list->size) {
    DEBUG_LOG("Index is invalid.");
    return NULL;
  }
  t_student *student = list->students[index];
  for (int i = index; i < list->size - 1; i++) {
    list->students[i] = list->students[i + 1];
  }
  return student;
}

int student_list_find(const t_student_list *list, const t_student *student) {
  if (list == NULL) {
    DEBUG_LOG("Student list is null");
    return -1;
  }
  if (student == NULL) {
    DEBUG_LOG("Student is null");
    return -1;
  }
  for (int i = 0; i < list->size; i++) {
    if (student_equal(list->students[i], student)) {
      SUCCESS_LOG("Student found");
      return i;
    }
  }
  SUCCESS_LOG("Student not found");
  return -1;
}
int student_list_find_by_name(const t_student_list *list, const char *name) {
  if (list == NULL) {
    DEBUG_LOG("Student list is null");
    return -1;
  }
  if (name == NULL) {
    DEBUG_LOG("Student is null");
    return -1;
  }
  for (int i = 0; i < list->size; i++) {
    if (!strcmp(list->students[i], name)) {
      SUCCESS_LOG("Student found");
      return i;
    }
  }
  SUCCESS_LOG("Student not found");
  return -1;
}

int student_list_find_by_grade(const t_student_list *list, const char *grade) {
  if (list == NULL) {
    DEBUG_LOG("Student list is null");
    return -1;
  }
  if (grade == NULL) {
    DEBUG_LOG("Student is null");
    return -1;
  }
  for (int i = 0; i < list->size; i++) {
    if (!strcmp(list->students[i], grade)) {
      SUCCESS_LOG("Student found");
      return i;
    }
  }
  SUCCESS_LOG("Student not found");
  return -1;
}

int student_list_resize(t_student_list *list, const int capacity) {
  if (list == NULL) {
    DEBUG_LOG("Student list is null");
    return -1;
  }
  if (list->capacity > capacity) {
    SUCCESS_LOG("List does not need resizing");
    return 0;
  }
  t_student **new_container =
      (t_student **)calloc(capacity, sizeof(t_student *));
  if (new_container == NULL) {
    DEBUG_LOG("Failed to allocate memory for new container");
    return -1;
  }
  for (int i = 0; i < list->size; i++) {
    new_container[i] = list->students[i];
  }
  free(list->students);
  list->students = new_container;
  list->capacity = capacity;
  return 1;
}

#endif /* SRC_STUDENT_LIST */
