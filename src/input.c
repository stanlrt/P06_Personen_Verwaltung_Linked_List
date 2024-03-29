/**
 * @file input.c
 * @brief This file contains utility functions for handling user input.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    /* discard characters */
  }
}

bool trimNewLineCharacter(char *string) {
  int length = strlen(string);
  if (string[length - 1] == '\n') {
    string[length - 1] = '\0';
    return true;
  }
  return false;
}

void clean_input(char *input) {
  trimNewLineCharacter(input);
  clear_input_buffer();
}
