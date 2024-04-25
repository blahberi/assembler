/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_MACRO_TABLE_H
#define ASSEMBLER_MACRO_TABLE_H

#include "line_list.h"

typedef struct Macro { /* Represents a macro */
    char *name;
    LineList *lines;
} Macro;

Macro *construct_macro(const char *name); /* Construct a new macro */

void init_macro_table(); /* Initialize the macro table */
void insert_macro(Macro *macro); /* Insert a macro to the table */
Macro* find_macro(const char *name); /* Find a macro in the table */
bool is_macro(const char *name); /* Check if a macro exists in the table */

#endif /* ASSEMBLER_MACRO_TABLE_H */
