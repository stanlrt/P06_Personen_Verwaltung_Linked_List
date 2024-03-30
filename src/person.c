/**
 * @file person.c
 * @brief This file contains the implementation of the `Person` struct and
 * related functions.
 */

#include "person.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

int person_compare(const void* personA, const void* personB) {
  Person* a = (Person*)personA;
  Person* b = (Person*)personB;
  if (strcmp(a->lastName, b->lastName) > 0)
    return 1;
  else if (strcmp(a->lastName, b->lastName) < 0)
    return -1;

  if (strcmp(a->firstName, b->firstName) > 0)
    return 2;
  else if (strcmp(a->firstName, b->firstName) < 0)
    return -2;

  if (a->age - b->age > 0)
    return 3;
  else if (a->age - b->age < 0)
    return -3;

  return 0;
}

void free_person(Person* person) { free(person); }

Person* prompt_user_for_person(void) {
  Person* person = malloc(sizeof(Person));
  printf("Specify the person's details.\n");
  read_string_of_maximum_length(person->firstName, "First name: ", NAME_LEN);
  read_string_of_maximum_length(person->lastName, "Last name: ", NAME_LEN);
  read_integer(&person->age, "Age: ");
  return person;
}

char* person_to_string(const Person* person) {
  int requiredSize =
      snprintf(NULL, 0, "First name: %s, Last name: %s, Age: %d",
               person->firstName, person->lastName, person->age) +
      1;
  char* string = malloc(requiredSize);
  if (string != NULL) {
    sprintf(string, "First name: %s \t Last name: %s \t Age: %d",
            person->firstName, person->lastName, person->age);
  }
  return string;
}
