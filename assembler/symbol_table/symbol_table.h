//
// Author: Eitan H.
//

#ifndef ASSEMBLER_SYMBOL_TABLE_H
#define ASSEMBLER_SYMBOL_TABLE_H

#include "../../config.h"
#include "symbol.h"
#include "symbol_node.h"

#include <stdio.h>
#include <stdbool.h>

// typedefs for structs
typedef struct symbol_table SymbolTable;

struct symbol_table {
    SymbolNode* symbolTable[SYMBOL_TABLE_SIZE];
    Symbol* (*find)(SymbolTable* this, const char* name);
    void (*insert)(SymbolTable* this, Symbol* symbol);
    bool (*is_in)(SymbolTable *this, const char *name);
    void (*print)(SymbolTable *this);
    void (*free)(SymbolTable *table);
};

// Function prototypes
SymbolTable* construct_symbol_table();

#endif //ASSEMBLER_SYMBOL_TABLE_H
