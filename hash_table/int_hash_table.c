//
// Author: Eitan H.
//

#include <malloc.h>
#include "int_hash_table.h"

void insert(struct IntHashTable *this, const char* key, int value){
    int* p = malloc(sizeof(int));
    *p = value;
    this->base->insert(this->base, key, p);
}

int find(struct IntHashTable *this, const char* key){
    int* p = this->base->find(this->base, key);
    return p == NULL ? -1 : *p;
}

void free_table(struct IntHashTable *this){
    this->base->free(this->base);
    free(this->base);
}

struct IntHashTable* construct_int_hash_table(){
    struct IntHashTable* hash_table = malloc(sizeof(struct IntHashTable));
    hash_table->base = construct_hash_table();
    hash_table->insert = insert;
    hash_table->find = find;
    hash_table->free = free_table;
    return hash_table;
}