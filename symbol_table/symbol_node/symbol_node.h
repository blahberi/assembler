//
// Author: Eitan H.
//

#ifndef ASSEMBLER_SYMBOL_NODE_H
#define ASSEMBLER_SYMBOL_NODE_H

#include "../symbol/symbol.h"


typedef struct symbol_node {
    Symbol* symbol;
    struct symbol_node *next;
} SymbolNode;

Symbol* find_symbol(SymbolNode* head, const char* name);

#endif //ASSEMBLER_SYMBOL_NODE_H
