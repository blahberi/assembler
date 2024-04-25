//
// Author: Eitan H.
//

#include <string.h>
#include "../../hash_table/hash_table.h"
#include "macro_table.h"
#include "../../memory_allocator/memory_allocator.h"

typedef struct MacroTable {
    HashTable *base;
} MacroTable;

MacroTable *MACRO_TABLE;

Macro *construct_macro(const char *name) {
    Macro *macro = malloc_track_global(sizeof(Macro));
    macro->name = malloc_track_global(strlen(name) + 1);
    strcpy(macro->name, name);
    macro->lines = construct_line_list();
    return macro;
}

void init_macro_table(){
    MACRO_TABLE = malloc_track_global(sizeof(MacroTable));
    MACRO_TABLE->base = construct_hash_table();
}

void insert_macro(Macro *macro) {
    MACRO_TABLE->base->insert(MACRO_TABLE->base, macro->name, macro);
}

Macro *find_macro(const char *name) {
    return MACRO_TABLE->base->find(MACRO_TABLE->base, name);
}

bool is_macro(const char *name) {
    return MACRO_TABLE->base->is_in(MACRO_TABLE->base, name);
}