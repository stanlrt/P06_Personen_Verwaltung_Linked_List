/**
 * @file command_parsing.c
 * @brief This file contains logic to prompt and parse commands from the
 * console.
 *
 * This file contains the implementation of the command parsing logic. This
 * logic is responsible for prompting the user for a command, parsing the
 * command, and executing the command.
 */

#include "command.h"

#include <stdio.h>
#include <stdlib.h>

#include "command-handlers.h"
#include "input.h"
#include "person.h"

void print_commands(Command* commandList, size_t commandCount) {
  for (int i = 0; i < commandCount; ++i) {
    printf("Enter [%s] to %s\n", commandList[i].keyword,
           commandList[i].description);
  }
}

/**
 * @brief Returns the length of the longest keyword in the given list of
 * commands, including the null terminator.
 * @param commandList The list of commands.
 * @param commandCount The number of commands in the list.
 * @return The length of the longest keyword in the list of commands, including
 * the null terminator.
 */
static size_t get_length_of_longest_keyword(Command* commandList,
                                            size_t commandCount) {
  size_t maxLength = 0;
  for (int i = 0; i < commandCount; ++i) {
    size_t length = strlen(commandList[i].keyword);
    if (length > maxLength) {
      maxLength = length;
    }
  }
  return maxLength + 1;
}

/**
 * Returns a string containing all the valid keywords in the given list of
 * commands.
 *
 * @param commands The list of commands.
 * @param commandCount The number of commands in the list.
 * @return A string containing all the valid keywords in the list of commands.
 */
static bool is_valid_keyword(char* keyword, Command* commandList,
                             size_t commandCount) {
  for (size_t i = 0; i < commandCount; i++) {
    if (strcmp(keyword, commandList[i].keyword) == 0) return true;
  }
  return false;
}

/**
 * Returns the command with the given keyword and frees the memory allocated for
 * the keyword.
 *
 * @param commandList The list of commands.
 * @param commandCount The number of commands in the list.
 * @param keyword The keyword of the command to return.
 * @return The command with the given keyword.
 */
static Command* get_command_by_keyword(Command* commandList,
                                       size_t commandCount, char* keyword) {
  for (int i = 0; i < commandCount; ++i) {
    if (strcmp(commandList[i].keyword, keyword) == 0) {
      free(keyword);
      return &commandList[i];
    }
  }
  return NULL;
}

Command* prompt_user_for_valid_command(Command* commandList,
                                       size_t commandCount) {
  size_t longestKeywordLengthIncludingNullTerminator =
      get_length_of_longest_keyword(commandList, commandCount);
  char* commandKeywordInputByUser = (char*)malloc(
      (longestKeywordLengthIncludingNullTerminator) * sizeof(char));
  print_commands(commandList, commandCount);
  while (true) {
    read_string_of_maximum_length(commandKeywordInputByUser, "",
                                  longestKeywordLengthIncludingNullTerminator);
    if (is_valid_keyword(commandKeywordInputByUser, commandList,
                         commandCount)) {
      return get_command_by_keyword(commandList, commandCount,
                                    commandKeywordInputByUser);
    } else {
      printf("Unrecognised command.\n");
    }
  }
}

bool execute_command(Command* command, Command* commandList,
                     size_t commandCount, void* (*argumentPrompting)(void)) {
  for (int i = 0; i < commandCount; ++i) {
    if (strcmp(command->keyword, commandList[i].keyword) == 0) {
      void* commandArgument = NULL;
      if (commandList[i].takesArgument) {
        commandArgument = argumentPrompting();
      }
      commandList[i].executionFunction(commandArgument);
      return true;
    }
  }

  printf("Invalid command. Try again.\n");
  return false;
}