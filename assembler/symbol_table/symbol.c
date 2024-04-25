//
// Author: Eitan H.
//

#include "symbol.h"
#include "../../memory_allocator/memory_allocator.h"


#include <string.h>

// Construct a new Symbol
Symbol *construct_symbol(const char *name, LABEL_TYPE type, int value, bool is_entry) {
    Symbol* symbol = malloc_track_global(sizeof(Symbol));
    strncpy(symbol->name, name, MAX_LABEL_LENGTH - 1);
    symbol->name[MAX_LABEL_LENGTH - 1] = '\0';
    symbol->value = value;
    symbol->type = type;
    symbol->is_entry = is_entry;
    return symbol;
}