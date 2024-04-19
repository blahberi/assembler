//
// Author: Eitan H.
//

#ifndef ASSEMBLER_SYMBOL_H
#define ASSEMBLER_SYMBOL_H

#include "../../config/config.h"

typedef struct symbol {
    char name[MAX_LABEL_LENGTH];
    int value;
    int is_external;

    void (*free)(struct symbol*);
} Symbol;

Symbol* construct_symbol(const char* name, int value, int is_external);

#endif //ASSEMBLER_SYMBOL_H
