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
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "person.h"

LinkedList* globalPersonList = NULL;

static void initialiseList() {
  if (globalPersonList == NULL) {
    globalPersonList = createLinkedList();
  }
}

bool execute_insert_command(void* person_to_insert) {
  Person* person = (Person*)person_to_insert;
  initialiseList();
  sortedInsert(globalPersonList, person, person_compare);
}

bool execute_remove_command(void* person_to_remove) {
  Person* person = (Person*)person_to_remove;
  for (size_t i = 0; i < globalPersonList->size; i++) {
    Person* currentPerson = (Person*)getNodeAtIndex(globalPersonList, i)->data;
    if (strcmp(currentPerson->lastName, person->lastName) == 0 &&
        strcmp(currentPerson->firstName, person->firstName) == 0 &&
        currentPerson->age == person->age) {
      deleteAtIndex(globalPersonList, i);
      return true;
    }
  }
  return false;
}

bool execute_show_command(void* person_to_show) {
  Person* person = (Person*)person_to_show;
  if (globalPersonList->size == 0) {
    printf("The list is empty.\n");
    return true;
  }
  for (size_t i = 0; i < globalPersonList->size; i++) {
    Person* currentPerson = (Person*)getNodeAtIndex(globalPersonList, i)->data;
    printf("%i \t %s \n", i, person_to_string(currentPerson));
  }
  return true;
}

bool execute_clear_command(void* person_to_clear) {
  Person* person = (Person*)person_to_clear;
  deleteList(globalPersonList);
  return true;
}

bool execute_end_command(void* person_to_end) {
  printf("Thanks for using the program!");
  exit(0);
}
