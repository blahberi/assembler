//
// Author: Eitan H.
//

#ifndef ASSEMBLER_SYMBOL_TABLE_H
#define ASSEMBLER_SYMBOL_TABLE_H

#include "../../config.h"
#include "symbol.h"
#include "../../hash_table/hash_table.h"

#include <stdio.h>
#include <stdbool.h>

// typedefs for structs
typedef struct SymbolTable {
    HashTable* base;
    void (*insert)(struct SymbolTable* this, Symbol* symbol);
    Symbol* (*find)(struct SymbolTable* this, const char* name);
    bool (*is_in)(struct SymbolTable* this, const char* name);
    void (*foreach)(struct SymbolTable* this, void (*callback)(Symbol* symbol, void* context), void* context);
    void (*free)(struct SymbolTable* this);
} SymbolTable;

// Function prototypes
SymbolTable* construct_symbol_table();

#endif //ASSEMBLER_SYMBOL_TABLE_H
