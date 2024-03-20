#ifndef INC_COMMANDS
#define INC_COMMANDS

int gtuStudentGrades(const char *filename);
int addStudentGrade(const char *filename, const char *studentName,
                    const char *grade);
int searchStudent(const char *filename, const char *studentName);
int sortAll(const char *filename);
int showAll(const char *filename);
int listGrades(const char *filename);
int listSome(const char *filename, int entryCount, int pageIndex);
int gtuStudentGradesNoArg();

#endif /* INC_COMMANDS */
