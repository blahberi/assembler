//
// Author: Eitan H.
//

#include <malloc.h>
#include "symbol_table.h"
#include "symbol.h"

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
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Node* node = this->base->buckets[i];
        while (node) {
            Symbol* symbol = (Symbol*) node->value;
            callback(symbol, context);
            node = node->next;
        }
    }
}

static void symbol_table_free(SymbolTable* this) {
    this->base->free(this->base);
    free(this);
}

SymbolTable* construct_symbol_table() {
    struct SymbolTable* table = malloc(sizeof(struct SymbolTable));
    if (!table) return NULL;

    table->base = construct_hash_table();
    if (!table->base) {
        free(table);
        return NULL;
    }

    table->insert = insert;
    table->find = find;
    table->is_in = is_in;
    table->foreach = foreach;
    table->free = symbol_table_free;

    return table;
}