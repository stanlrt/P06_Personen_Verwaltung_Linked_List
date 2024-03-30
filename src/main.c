/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Lab implementation
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "command-handlers.h"
#include "command.h"
#include "person.h"

/**
 * The list of commands that the user can enter
 */
Command commandList[] = {
    {"I", execute_insert_command, true, "Insert a person"},
    {"R", execute_remove_command, true, "Remove a person"},
    {"S", execute_show_command, false, "Show all people"},
    {"C", execute_clear_command, false, "Clear the list of people"},
    {"E", execute_end_command, false, "End the program"},
};

const size_t commandCount = sizeof(commandList) / sizeof(Command);

/**
 * @brief Main entry point.
 * @param[in] argc  The size of the argv array.
 * @param[in] argv  The command line arguments...
 * @returns Returns EXIT_SUCCESS (=0) on success, EXIT_FAILURE (=1) there is an
 * expression syntax error.
 */
int main(int argc, char* argv[]) {
  // BEGIN-STUDENTS-TO-ADD-CODE
  printf(
      "Welcome. This program allows you to manipulate a record of people.\n\n");
  while (true) {
    execute_command(prompt_user_for_valid_command(commandList, commandCount),
                    commandList, commandCount, (void*)prompt_user_for_person);
    // printBufferContentsForDebugging();
    printf("\n\n");
  }

  // END-STUDENTS-TO-ADD-CODE
  return EXIT_SUCCESS;
}
