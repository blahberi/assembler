//
// Author: Eitan H.
//

#ifndef ASSEMBLER_HASH_TABLE_H
#define ASSEMBLER_HASH_TABLE_H

#include "node.h"
#include "../config.h"
#include <stdbool.h>

typedef struct HashTable {
    Node* buckets[HASH_TABLE_SIZE];
    int size;
    void (*insert)(struct HashTable* this, const char* key, void* value);
    void* (*find)(struct HashTable* this, const char* key);
    bool (*is_in)(struct HashTable* this, const char* key);
    void (*foreach)(struct HashTable* this, void (*callback)(const char* key, void* value, void* context), void* context);
} HashTable;

HashTable * construct_hash_table();

#endif //ASSEMBLER_HASH_TABLE_H
