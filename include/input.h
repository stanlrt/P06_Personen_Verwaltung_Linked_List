#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Reads an integer from the user, and stores it in the provided buffer.
 *
 * @param userInput The integer to read into
 * @param prompt The prompt to display to the user
 */
void read_integer(int* userInput, char* prompt);

/**
 * @brief Reads a string of maximum length from the user, and stores it in the
 * provided buffer.
 *
 * @param userInput The string to read into
 * @param prompt The prompt to display to the user
 * @param maximumLength The maximum length of the string, including the null
 * terminator
 * @note The length should include the null terminator.
 */
void read_string_of_maximum_length(char* userInput, char* prompt,
                                   int maximumLength);

#endif
