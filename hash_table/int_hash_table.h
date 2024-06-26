/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_INT_HASH_TABLE_H
#define ASSEMBLER_INT_HASH_TABLE_H

#include "hash_table.h"

typedef struct IntHashTable { /* Ontop of the HashTable class, this hash table has integer values instead of void* */
    HashTable *base; /* Base hash table */
    void (*insert)(struct IntHashTable *this, const char* key, int value); /* Insert a key-value pair into the hash table */
    int (*find)(struct IntHashTable *this, const char* key); /* Find a value by key */
} IntHashTable;

struct IntHashTable* construct_int_hash_table();

#endif /* ASSEMBLER_INT_HASH_TABLE_H */
