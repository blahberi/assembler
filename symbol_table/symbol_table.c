//
// Author: Eitan H.
//

#include "symbol_table.h"
#include "symbol_node.h"
#include "symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// djb2 hash function
unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % SYMBOL_TABLE_SIZE;
}

// Inserts a symbol into the symbol table
void insert(SymbolTable* this, Symbol* symbol) {
    unsigned long hash_value = hash(symbol->name);
    SymbolNode* node = (SymbolNode*)malloc(sizeof(SymbolNode));
    if (!node) {
        fprintf(stderr, "Failed to allocate memory for SymbolNode\n");
        return;
    }
    node->symbol = symbol;
    node->next = this->symbolTable[hash_value];
    this->symbolTable[hash_value] = node;
}

// Finds a symbol in the symbol table by name
Symbol* find(SymbolTable* this, const char* name) {
    unsigned long hash_value = hash(name);
    SymbolNode* node = this->symbolTable[hash_value];
    return find_symbol(node, name);
}

bool is_in(SymbolTable *this, const char *name) {
    if (this->find(this, name) == NULL) {
        return false;
    }
    return true;
}

// Frees all memory associated with the symbol table
void free_symbol_table(SymbolTable *table) {
    if (table == NULL) return;

    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        SymbolNode *node = table->symbolTable[i];
        while (node != NULL) {
            SymbolNode *temp = node;
            node = (SymbolNode *) node->next;
            free(temp);
        }
    }
    free(table);
}

// Constructs a new SymbolTable
SymbolTable *construct_symbol_table() {
    SymbolTable* symbolTable = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (!symbolTable) {
        fprintf(stderr, "Failed to allocate memory for SymbolTable\n");
        return NULL;
    }
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        symbolTable->symbolTable[i] = NULL;
    }
    symbolTable->find = find;
    symbolTable->insert = insert;
    symbolTable->is_in = is_in;
    symbolTable->free = free_symbol_table;
    return symbolTable;
}