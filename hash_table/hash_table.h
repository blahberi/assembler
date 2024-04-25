/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_HASH_TABLE_H
#define ASSEMBLER_HASH_TABLE_H

#include "node.h"
#include "../config.h"
#include <stdbool.h>

typedef struct HashTable { /* Hash table data structure */
    Node* buckets[HASH_TABLE_SIZE]; /* Array of hash entries (linked lists) */
    int size;
    void (*insert)(struct HashTable* this, const char* key, void* value); /* Insert a key-value pair into the hash table */
    void* (*find)(struct HashTable* this, const char* key); /* Find a value by key */
    bool (*is_in)(struct HashTable* this, const char* key); /* Check if a key is in the hash table */
    void (*foreach)(struct HashTable* this, void (*callback)(const char* key, void* value, void* context), void* context); /* Iterate over the hash table */
} HashTable;

HashTable * construct_hash_table(); /* Construct a new hash table */

#endif /* ASSEMBLER_HASH_TABLE_H */
