//
// Author: Eitan H.
//

#include <malloc.h>
#include "int_hash_table.h"
#include "../memory_tracker/scope_memory_tracker.c.h"

void insert(struct IntHashTable *this, const char* key, int value){
    int* p = malloc_track(sizeof(int));
    *p = value;
    this->base->insert(this->base, key, p);
}

int find(struct IntHashTable *this, const char* key){
    int* p = this->base->find(this->base, key);
    return p == NULL ? -1 : *p;
}

struct IntHashTable* construct_int_hash_table(){
    struct IntHashTable* hash_table = malloc_track(sizeof(struct IntHashTable));
    hash_table->base = construct_hash_table();
    hash_table->insert = insert;
    hash_table->find = find;
    return hash_table;
}