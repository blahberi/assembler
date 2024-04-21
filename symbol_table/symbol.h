//
// Author: Eitan H.
//

#ifndef ASSEMBLER_SYMBOL_H
#define ASSEMBLER_SYMBOL_H

#include <stdbool.h>
#include "../config.h"

typedef enum {
    MDEFINE,
    DATA,
    CODE,
    EXTERN
} LABEL_TYPE;

typedef struct symbol {
    char name[MAX_LABEL_LENGTH+1]; // +1 for null terminator
    LABEL_TYPE type; // MDEFINE, DATA, CODE
    int value;
    bool is_external; // Did the symbol come from .extern directive
    bool is_entry; // Did the symbol go through .entry directive
    void (*free)(struct symbol*); // Garbage collection
} Symbol;

Symbol *construct_symbol(const char *name, LABEL_TYPE type, int value, bool is_external, bool is_entry);

#endif //ASSEMBLER_SYMBOL_H
