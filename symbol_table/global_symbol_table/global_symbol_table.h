//
// Author: Eitan H.
//


#ifndef ASSEMBLER_GLOBAL_SYMBOL_TABLE_H
#define ASSEMBLER_GLOBAL_SYMBOL_TABLE_H

#include "../symbol/symbol.h"
#include <stdbool.h>

int create_global_symbol_table();
int destroy_global_symbol_table();
Symbol* symbol_table_find(const char *name);
void symbol_table_insert(Symbol *symbol);
bool symbol_table_is_in(const char *name);

#endif //ASSEMBLER_GLOBAL_SYMBOL_TABLE_H
