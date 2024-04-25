/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_SYMBOL_H
#define ASSEMBLER_SYMBOL_H

#include <stdbool.h>
#include "../../config.h"

typedef enum {
    MDEFINE_LABEL,
    DATA_LABEL,
    CODE_LABEL,
    EXTERN_LABEL
} LABEL_TYPE;

typedef struct symbol {
    char name[MAX_LABEL_LENGTH+1]; /* +1 for null terminator */
    LABEL_TYPE type; /* MDEFINE_LABEL, DATA_LABEL, CODE_LABEL */
    int value;
    bool is_entry; /* Did we apply .entry to this label? */
} Symbol;

Symbol *construct_symbol(const char *name, LABEL_TYPE type, int value, bool is_entry);

#endif /*ASSEMBLER_SYMBOL_H */
