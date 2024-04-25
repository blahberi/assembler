/*
 Author: Eitan H.
*/

#include <string.h>
#include "../../hash_table/hash_table.h"
#include "macro_table.h"
#include "../../memory_allocator/memory_allocator.h"

typedef struct MacroTable {
    HashTable *base;
} MacroTable;

MacroTable *MACRO_TABLE;

Macro *construct_macro(const char *name) { /* Construct a new macro */
    Macro *macro = malloc_track_global(sizeof(Macro)); /* Allocate memory for the macro */
    macro->name = malloc_track_global(strlen(name) + 1); /* Allocate memory for the macro name */
    strcpy(macro->name, name); /* Copy the name to the macro */
    macro->lines = construct_line_list(); /* Construct a new line list */
    return macro;
}

void init_macro_table(){ /* Initialize the macro table */
    MACRO_TABLE = malloc_track_global(sizeof(MacroTable)); /* Allocate memory for the macro table */
    MACRO_TABLE->base = construct_hash_table(); /* Construct a new hash table */
}

void insert_macro(Macro *macro) {
    MACRO_TABLE->base->insert(MACRO_TABLE->base, macro->name, macro);
}

Macro *find_macro(const char *name) { /* Find a macro in the table */
    return MACRO_TABLE->base->find(MACRO_TABLE->base, name);
}

bool is_macro(const char *name) { /* Check if a macro exists in the table */
    return MACRO_TABLE->base->is_in(MACRO_TABLE->base, name);
}