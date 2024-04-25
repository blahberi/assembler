/*
Author: Eitan H.
*/

#include "symbol_table.h"
#include "symbol.h"
#include "../../memory_allocator/memory_allocator.h"

static void insert(SymbolTable* this, Symbol* symbol) { /* Insert a symbol to the table */
    this->base->insert(this->base, symbol->name, symbol);
}

static Symbol* find(SymbolTable* this, const char* name) { /* Find a symbol in the table */
    return (Symbol*) this->base->find(this->base, name);
}

static bool is_in(SymbolTable* this, const char* name) { /* Check if a symbol exists in the table */
    return this->base->is_in(this->base, name);
}

static void foreach(SymbolTable* this, void (*callback)(Symbol* symbol, void* context), void* context) { /* Call a callback function for each symbol in the table */
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        Node* node = this->base->buckets[i];
        while (node) {
            Symbol* symbol = (Symbol*) node->value;
            callback(symbol, context);
            node = node->next;
        }
    }
}

SymbolTable* construct_symbol_table() { /* Construct a new symbol table */
    struct SymbolTable* table = malloc_track_global(sizeof(struct SymbolTable));
    table->base = construct_hash_table();

    table->insert = insert;
    table->find = find;
    table->is_in = is_in;
    table->foreach = foreach;

    return table;
}