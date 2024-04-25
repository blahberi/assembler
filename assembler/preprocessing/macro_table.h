/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_MACRO_TABLE_H
#define ASSEMBLER_MACRO_TABLE_H

#include "line_list.h"

typedef struct Macro {
    char *name;
    LineList *lines;
} Macro;

Macro *construct_macro(const char *name);

void init_macro_table();
void insert_macro(Macro *macro);
Macro* find_macro(const char *name);
bool is_macro(const char *name);

#endif /* ASSEMBLER_MACRO_TABLE_H */
