#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>
#include <stdio.h>

#include "person.h"

/**
 * A structure representing a mapping between a command keyword and its
 * associated functionality.
 *
 * This includes the command's execution function,
 * whether it requires an argument, and a description of the command for user
 * reference.
 */
typedef struct {
  /**
   * The keyword (string) that the user can enter to execute the command. This
   * is the trigger word for the command functionality.
   */
  char* keyword;

  /**
   * The function to execute when the command is entered. This function pointer
   * should point to the specific function that implements the command's action.
   * The function takes a pointer to a Person object as its argument, allowing
   * the command to operate on or utilize person data.
   */
  bool (*executionFunction)(void*);

  /**
   * Whether the command takes an argument. This boolean value indicates if the
   * command requires additional data from the user to execute properly. If
   * true, the command execution mechanism should prompt the user for this
   * argument.
   */
  bool takesArgument;

  /**
   * The description of the command. This is a brief text explaining what the
   * command does, intended to be displayed to the user as part of help or
   * documentation output.
   */
  char* description;

} Command;

/**
 * Helper function that prints the keyword and description for each command in
 * the given list.
 *
 * @param commandList The list of commands.
 * @param commandCount The number of commands in the list.
 */
void print_commands(Command* commandList, size_t commandCount);

/**
 * Prompts the user for a command contained in the given list, by displaying the
 * list of possible keywords.
 *
 * @remark The function returns only once a valid command has been entered.
 *
 * @param commandList The list of commands.
 * @param commandCount The number of commands in the list.
 * @return The valid command entered by the user.
 */
Command* prompt_user_for_valid_command(Command* commandList,
                                       size_t commandCount);

/**
 * Executes the given command, prompting the user for an argument if required.
 * If the command is invalid, a message is displayed.
 *
 * @param command The command to execute.
 * @param commandList The list of commands.
 * @param commandCount The number of commands in the list.
 * @param argumentPrompting The function to prompt the user for a command
 * argument.
 * @return `true` if the command was executed successfully, `false` otherwise.
 */
bool execute_command(Command* command, Command* commandList,
                     size_t commandCount, void* (*argumentPrompting)(void));

#endif  // COMMAND_H
