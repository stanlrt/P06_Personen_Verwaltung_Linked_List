/**
 * @file command_handlers.c
 * @brief This file contains the handler functions for each existing command.
 *
 * This file contains the implementation of the handler functions for each
 * existing command.
 *
 * Each handler function takes a pointer to a `Person` struct
 * and returns a boolean indicating whether the command was executed
 * successfully.
 */

#include <stdbool.h>
#include <stdio.h>

#include "person.h"

bool execute_insert_command(void* person_to_insert) {
  Person* person = (Person*)person_to_insert;
  printf("INSERTTTTT");
}

bool execute_remove_command(void* person_to_remove) {
  Person* person = (Person*)person_to_remove;
  printf("REMOVE");
}

bool execute_show_command(void* person_to_show) {
  Person* person = (Person*)person_to_show;
  printf("SHOW");
}

bool execute_clear_command(void* person_to_clear) {
  Person* person = (Person*)person_to_clear;
  printf("CLEAR");
}

bool execute_end_command(void* person_to_end) {
  Person* person = (Person*)person_to_end;
  printf("END");
}
