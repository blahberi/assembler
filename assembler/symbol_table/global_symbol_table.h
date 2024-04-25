/*
 Author: Eitan H.
*/


#ifndef ASSEMBLER_GLOBAL_SYMBOL_TABLE_H
#define ASSEMBLER_GLOBAL_SYMBOL_TABLE_H

#include "symbol.h"
#include <stdbool.h>

int init_global_symbol_table(); /* Initialize the global symbol table */
Symbol* symbol_table_find(const char *name); /* Find a symbol in the global symbol table */
void symbol_table_insert(Symbol *symbol); /* Insert a symbol into the global symbol table */
bool symbol_table_is_in(const char *name); /* Check if a symbol is in the global symbol table */
void symbol_table_update_address(int ic); /* Update the address of all symbols in the global symbol table */
void write_entry_file(const char *filepath); /* Write the .ent file */

#endif /* ASSEMBLER_GLOBAL_SYMBOL_TABLE_H */
