//
// Author: Eitan H.
//

#include "global_symbol_table.h"
#include "symbol_table.h"
#include <stdlib.h>

SymbolTable *SYMBOL_TABLE = NULL;
int create_global_symbol_table() {
    if (SYMBOL_TABLE){
        SYMBOL_TABLE->free(SYMBOL_TABLE);
    }
    SYMBOL_TABLE = construct_symbol_table();
    if (!SYMBOL_TABLE) {
        return 1;
    }
    return 0;
}

int destroy_global_symbol_table() {
    if (SYMBOL_TABLE) {
        SYMBOL_TABLE->free(SYMBOL_TABLE);
        SYMBOL_TABLE = NULL;
    }
    return 0;
}

Symbol* symbol_table_find(const char *name) {
    return SYMBOL_TABLE->find(SYMBOL_TABLE, name);
}

void symbol_table_insert(Symbol *symbol) {
    SYMBOL_TABLE->insert(SYMBOL_TABLE, symbol);
}

bool symbol_table_is_in(const char *name) {
    return SYMBOL_TABLE->is_in(SYMBOL_TABLE, name);
}

void symbol_table_update_address(int ic) {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        SymbolNode *node = SYMBOL_TABLE->symbolTable[i];
        while (node != NULL) {
            if (node->symbol->type == CODE) {
                node->symbol->value += 100;
            } else if (node->symbol->type == DATA) {
                node->symbol->value += 100 + ic;
            }
            node = node->next;
        }
    }
}

void symbol_table_print() {
    SYMBOL_TABLE->print(SYMBOL_TABLE);
}