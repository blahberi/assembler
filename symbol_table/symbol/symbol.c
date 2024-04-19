//
// Author: Eitan H.
//

#include "symbol.h"
#include "../../config/config.h"


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Construct a new Symbol
Symbol *construct_symbol(const char *name, int value, int is_external) {
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    if (!symbol) {
        fprintf(stderr, "Failed to allocate memory for Symbol\n");
        return NULL;
    }
    strncpy(symbol->name, name, MAX_LABEL_LENGTH - 1);
    symbol->name[MAX_LABEL_LENGTH - 1] = '\0';
    symbol->value = value;
    symbol->is_external = is_external;
    return symbol;
}

// Frees all memory associated with a symbol
void free_symbol(Symbol *symbol) {
    if (symbol == NULL) return;
    free(symbol);
}