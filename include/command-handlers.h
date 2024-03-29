#ifndef COMMAND_HANDLERS_H
#define COMMAND_HANDLERS_H

#include <stdbool.h>

#include "person.h"

bool execute_insert_command(void* person_to_insert);
bool execute_remove_command(void* person_to_remove);
bool execute_show_command(void* person_to_show);
bool execute_clear_command(void* person_to_clear);
bool execute_end_command(void* person_to_end);

#endif  // COMMAND_HANDLERS_H
