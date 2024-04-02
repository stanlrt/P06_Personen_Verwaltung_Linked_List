#ifndef COMMAND_HANDLERS_H
#define COMMAND_HANDLERS_H

#include <stdbool.h>

#include "person.h"

bool execute_insert_command(void* personToInsert);
bool execute_remove_command(void* personToRemove);
bool execute_show_command(void* personToShow);
bool execute_clear_command(void* personToClear);
bool execute_end_command(void* personToEnd);

#endif  // COMMAND_HANDLERS_H
