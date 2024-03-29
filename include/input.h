#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * Clears the input buffer
 */
void clear_input_buffer(void);

/**
 * Trims the new line character from the end of a string, in place.
 *
 * @param string The string to trim
 * @return `true` if the string was trimmed, `false` otherwise
 */
bool trimNewLineCharacter(char *string);

/**
 * Cleans the input by trimming the new line character and clearing the input
 * buffer.
 *
 * @param input The input to clean
 * @return The cleaned input
 */
void clean_input(char *input);

#endif
