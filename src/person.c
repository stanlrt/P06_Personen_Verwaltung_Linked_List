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

Person* create_person(char* lastName, char* firstName, int age) {
  Person* person = (Person*)malloc(sizeof(Person));
  if (person == NULL) {
    fprintf(stderr, "Failed to allocate memory for a new person.\n");
    return NULL;
  }
  strcpy(person->lastName, lastName);
  strcpy(person->firstName, firstName);
  person->age = age;
  return person;
}

int person_compare(const void* personA, const void* personB) {
  Person* a = (Person*)personA;
  Person* b = (Person*)personB;
  if (strcmp(a->lastName, b->lastName) > 0) {
    return 1;
  } else if (strcmp(a->lastName, b->lastName) < 0) {
    return -1;
  }

  if (strcmp(a->firstName, b->firstName) > 0) {
    return 2;
  } else if (strcmp(a->firstName, b->firstName) < 0) {
    return -2;
  }

  if (a->age > b->age) {
    return 3;
  } else if (a->age < b->age) {
    return -3;
  }

  return 0;
}

void free_person(Person* person) { free(person); }

Person* prompt_user_for_person(void) {
  printf("Specify the person's details.\n");
  char* firstName;
  char* lastName;
  int age;
  read_string_of_maximum_length(firstName, "First name: ", NAME_LEN);
  read_string_of_maximum_length(lastName, "Last name: ", NAME_LEN);
  read_integer(&age, "Age: ");
  Person* person = create_person(lastName, firstName, age);
  return person;
}

char* person_to_string(const Person* person, PrintMode mode) {
  const char* TEXT_STRING = "First name: %s \t Last name: %s \t Age: %d";
  const char* CSV_STRING = "%s,%s,%d";
  const char* SELECTED_MODE_TEXT;
  switch (mode) {
    case TEXT:
      SELECTED_MODE_TEXT = TEXT_STRING;
      break;
    case CSV:
      SELECTED_MODE_TEXT = CSV_STRING;
      break;
    default:
      fprintf(stderr, "Invalid print mode.\n");
      return NULL;
  }

  int requiredSize = snprintf(NULL, 0, SELECTED_MODE_TEXT, person->firstName,
                              person->lastName, person->age) +
                     1;
  char* string = malloc(requiredSize);
  if (string == NULL) {
    fprintf(stderr, "Failed to allocate memory for the stringified person.\n");
    return NULL;
  }
  if (string != NULL) {
    sprintf(string, SELECTED_MODE_TEXT, person->firstName, person->lastName,
            person->age);
  }
  return string;
}

Person* parse_person_from_string(const char* string, PrintMode mode) {
  Person* person = malloc(sizeof(Person));
  if (person == NULL) {
    fprintf(stderr, "Failed to allocate memory for a new person.\n");
    return NULL;
  }
  switch (mode) {
    case TEXT:
      sscanf(string, "First name: %[^\t] Last name: %[^\t] Age: %d",
             person->firstName, person->lastName, &person->age);
      break;
    case CSV:
      sscanf(string, "%[^,],%[^,],%d", person->firstName, person->lastName,
             &person->age);
      break;
  }
  return person;
}
