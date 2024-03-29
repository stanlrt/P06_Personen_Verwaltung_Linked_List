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

int person_compare(const Person* personA, const Person* personB) {
  if (strcmp(personA->name, personB->name) > 0)
    return 1;
  else if (strcmp(personA->name, personB->name) < 0)
    return -1;

  if (strcmp(personA->name, personB->name) > 0)
    return 2;
  else if (strcmp(personA->name, personB->name) < 0)
    return -2;

  if (personA->age - personB->age > 0)
    return 3;
  else if (personA->age - personB->age < 0)
    return -3;

  return 0;
}

void free_person(Person* person) { free(person); }

Person* prompt_user_for_person(void) {
  Person* person = malloc(sizeof(Person));

  printf("First name: ");
  fgets(person->firstName, NAME_LEN, stdin);
  clean_input(person->firstName);

  printf("Last name: ");
  fgets(person->name, NAME_LEN, stdin);
  clean_input(person->name);

  printf("Age: ");
  scanf("%d", &person->age);
  return person;
}

char* person_to_string(const Person* person) {
  int requiredSize = snprintf(NULL, 0, "First name: %s, Last name: %s, Age: %d",
                              person->firstName, person->name, person->age) +
                     1;

  char* string = malloc(requiredSize);
  if (string != NULL) {
    sprintf(string, "First name: %s, Last name: %s, Age: %d", person->firstName,
            person->name, person->age);
  }
  return string;
}
