//
// Author: Eitan H. .
//

#include "global_symbol_table.h"
#include "../table/symbol_table.h"
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
        free(SYMBOL_TABLE);
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