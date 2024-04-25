/*
Author: Eitan H.
*/

#include "symbol_table.h"
#include "symbol.h"
#include "../../memory_allocator/memory_allocator.h"

static void insert(SymbolTable* this, Symbol* symbol) {
    this->base->insert(this->base, symbol->name, symbol);
}

static Symbol* find(SymbolTable* this, const char* name) {
    return (Symbol*) this->base->find(this->base, name);
}

static bool is_in(SymbolTable* this, const char* name) {
    return this->base->is_in(this->base, name);
}

static void foreach(SymbolTable* this, void (*callback)(Symbol* symbol, void* context), void* context) {
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

SymbolTable* construct_symbol_table() {
    struct SymbolTable* table = malloc_track_global(sizeof(struct SymbolTable));
    table->base = construct_hash_table();

    table->insert = insert;
    table->find = find;
    table->is_in = is_in;
    table->foreach = foreach;

    return table;
}