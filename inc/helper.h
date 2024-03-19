#ifndef INC_HELPER
#define INC_HELPER

/**
 * Counts the number of arguments in a string.
 *
 * This function takes a string as input and counts the number of arguments in
 * the string. An argument is defined as a sequence of non-space/NULL
 * characters or characters sequence between double-quotes. The function
 * returns the number of arguments in the string or -1 if there is an error.
 *
 * @param str The input string.
 * @return The number of arguments in the string. This value is always
 * non-negative and maxes out at BUFFER_SIZE. If there is an error, the function
 * returns -1.
 */
int count_args(const char *str);

/**
 * Counts the length of the argument string.
 *
 * This function takes a string as input and counts the length of the first
 * argument in the string. An argument is defined as a sequence of
 * non-space/NULL characters.
 *
 * @param str The input string.
 * @return The length of the string. This value is always non-negative and maxes
 * out at BUFFER_SIZE.
 */
int count_arg_length(const char *str);

/**
 * Clears the standard input.
 *
 * This function reads from the standard input until the end of the line or the
 * end of the file is reached. This function is useful to clear the standard
 * input after an error occurred.
 */
void clear_stdin();

/**
 * Frees the memory allocated for an array of strings and its elements.
 *
 * @param args The array of strings to free.
 */
void free_args(char **args);

#endif /* INC_HELPER */
