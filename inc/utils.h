#ifndef INC_UTILS
#define INC_UTILS

typedef enum e_command {
  CMD_INVALID,
  CMD_EXIT,
  CMD_HELP,
  CMD_CREATE,
  CMD_ADD
} t_command;

/**
 * Reads a line from the standard input and returns it as a dynamically
 * allocated string. The newline character is not included in the string. If an
 * error occurs, the function clears the standard input and returns NULL.
 *
 * @return A pointer to the dynamically allocated string containing the read
 * line. The caller is responsible for freeing the memory allocated for the
 * string.
 * @return NULL if an error occurred.
 */
char *read_line_from_stdin();

/**
 * Parses a line of text and extracts the arguments into an array of strings.
 * The seperator is a space.
 *
 * @param line The line of text to parse. This string is not modified.
 *
 * @return An array of strings containing the extracted arguments. The array is
 * null terminated. The caller is responsible for freeing the memory allocated
 * for the array and its elements.
 * @return NULL if an error occurred.
 */
char **get_args_from_line(const char *line);

/**
 * Extracts the command from a line of text.
 *
 * @param line The line of text to parse. This string is not modified.
 *
 * @return The command extracted from the line. This value is always valid.
 */
t_command extract_command(const char *line);

/**
 * Prints the help message.
 */
void help_command();

/**
 * Creates a file with the given name. The file is created using the child
 * process. The parent process waits for the child process to finish.
 *
 * @param filename A pointer to a pointer to a string that will be set to the
 * name of the file created.
 * @param args The arguments passed to the command. The first argument is the
 * command itself and the second argument is the name of the file to create.
 * @param isChild A pointer to an integer that is set to 1 if the current
 * process is the child process and 0 if it is the parent process.
 *
 * @return 0 if the file was created successfully.
 * @return -1 if an error occurred.
 */
int create_file_with_fork(char **filename, const char **args, int *isChild);

/**
 * Adds a student using the fork system call.
 *
 * This function takes an array of arguments `args` and a pointer `isChild`.
 * It uses the fork system call to create a child process, which then executes
 * the specified command with the given arguments. The parent process waits
 * for the child process to complete.
 *
 * @param filename A pointer to a pointer to a string of the filename the
 * student will be added to.
 * @param args An array of arguments to be passed to the command.
 * @param isChild A pointer to an integer that will be set to 1 if the current
 * process is the child process, and 0 if it is the parent process.
 *
 * @return Returns 0 on success, or -1 on failure.
 */

int add_student_with_fork(const char *filename, const char **args,
                          int *isChild);
#endif /* INC_UTILS */
