/**
 * @file input.c
 * @brief This file contains utility functions for handling user input.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define INPUT_READY_SYMBOL ">>> "

static int clear_input_buffer(void) {
  int charInBufferCount = 0;
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    charInBufferCount++;
  }
  printf("\n");
  return charInBufferCount;
}

void read_integer(int* inputDestination, char* prompt) {
  bool isValidInput = false;
  do {
    printf("%s\n%s", prompt, INPUT_READY_SYMBOL);
    if (scanf("%d", inputDestination) == 1) {
      isValidInput = true;
    } else {
      printf("Invalid input. Please enter an integer.\n");
    }
    clear_input_buffer();
  } while (!isValidInput);
}

void read_string_of_maximum_length(char* inputDestination, char* prompt,
                                   int maximumLengthIncludingNullTerminator) {
  if (maximumLengthIncludingNullTerminator <= 1) return;
  char tempUserInput[maximumLengthIncludingNullTerminator];
  char formatString[16];
  snprintf(formatString, sizeof(formatString), "%%%ds",
           maximumLengthIncludingNullTerminator - 1);

  bool isValidInput = false;
  do {
    printf("%s\n%s", prompt, INPUT_READY_SYMBOL);
    // Attempt to read a string within the maximum length.
    if (scanf(formatString, tempUserInput) == 1) {
      // Clear the buffer and check if there were excess characters.
      int excessChars = clear_input_buffer();
      if (excessChars == 0) {
        // If no excess characters, input is valid.
        isValidInput = true;
      } else {
        // Excess characters were entered, making the input invalid.
        printf("Invalid input. Please enter a string of maximum length %i.\n",
               maximumLengthIncludingNullTerminator - 1);
      }
    } else {
      // Failed to read a string, clear the buffer to remove invalid input.
      clear_input_buffer();
      printf("Invalid input. Please enter a string of maximum length %i.\n",
             maximumLengthIncludingNullTerminator - 1);
    }
  } while (!isValidInput);
  strncpy(inputDestination, tempUserInput,
          maximumLengthIncludingNullTerminator);
}

// TODO remove
static bool trim_new_line_character(char* string) {
  int length = strlen(string);
  if (string[length - 1] == '\n') {
    string[length - 1] = '\0';
    return true;
  }
  return false;
}

// TODO remove
static void clean_input(char* input) {
  // Remove newline character if present
  size_t input_length = strlen(input);
  bool inputWasSHorterThanMaximumLength =
      input_length > 0 && input[input_length - 1] == '\n';
  if (inputWasSHorterThanMaximumLength) {
    input[input_length - 1] = '\0';
  } else {
    // the input was longer than the maximum length, so some characters are
    // still in the buffer
    clear_input_buffer();
  }
}
