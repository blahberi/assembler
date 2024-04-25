//
// Author: Eitan H.
//

#ifndef ASSEMBLER_INT_HASH_TABLE_H
#define ASSEMBLER_INT_HASH_TABLE_H

#include "hash_table.h"

typedef struct IntHashTable {
    HashTable *base;
    void (*insert)(struct IntHashTable *this, const char* key, int value);
    int (*find)(struct IntHashTable *this, const char* key);
} IntHashTable;

struct IntHashTable* construct_int_hash_table();

#endif //ASSEMBLER_INT_HASH_TABLE_H
