/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_SYMBOL_TABLE_H
#define ASSEMBLER_SYMBOL_TABLE_H

#include "../../config.h"
#include "symbol.h"
#include "../../hash_table/hash_table.h"

#include <stdio.h>
#include <stdbool.h>

/* typedefs for structs */
typedef struct SymbolTable {
    HashTable* base; /* The base hash table */
    void (*insert)(struct SymbolTable* this, Symbol* symbol); /* Insert a symbol into the symbol table */
    Symbol* (*find)(struct SymbolTable* this, const char* name); /* Find a symbol in the symbol table */
    bool (*is_in)(struct SymbolTable* this, const char* name); /* Check if a symbol is in the symbol table */
    void (*foreach)(struct SymbolTable* this, void (*callback)(Symbol* symbol, void* context), void* context); /* Iterate over all symbols in the symbol table and apply a function */
} SymbolTable;

/* Function prototypes */
SymbolTable* construct_symbol_table(); /* Construct a symbol table */

#endif /* ASSEMBLER_SYMBOL_TABLE_H */
