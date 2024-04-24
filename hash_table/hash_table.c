//
// Author: Eitan H.
//

#include "hash_table.h"
#include <malloc.h>
#include <string.h>

// djb2 hash function
unsigned int hash(const char *key) {
    unsigned int hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_TABLE_SIZE;
}

static void insert(struct HashTable *this, const char* key, void* value){
    unsigned int index = hash(key);
    Node* new_node = malloc(sizeof(Node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = this->buckets[index];
    this->buckets[index] = new_node;
}

static void* find(struct HashTable *this, const char* key){
    unsigned int index = hash(key);
    Node* current = this->buckets[index];
    while (current != NULL){
        if (strcmp(current->key, key) == 0){
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

static bool is_in(struct HashTable *this, const char* key){
    return find(this, key) != NULL;
}

static void foreach(struct HashTable *this, void (*callback)(const char* key, void* value, void* context), void* context){
    for (int i = 0; i < HASH_TABLE_SIZE; i++){
        Node* current = this->buckets[i];
        while (current != NULL){
            callback(current->value, current->next, context);
            current = current->next;
        }
    }
}

static void free_table(struct HashTable *this){
    for (int i = 0; i < HASH_TABLE_SIZE; i++){
        Node* current = this->buckets[i];
        while (current != NULL){
            Node* next = current->next;
            free(current->value);
            free(current);
            current = next;
        }
    }
}

HashTable* construct_hash_table() {
    HashTable* table = malloc(sizeof(HashTable));
    table->size = HASH_TABLE_SIZE;
    table->insert = insert;
    table->find = find;
    table->is_in = is_in;
    table->free = free_table;
    for (int i = 0; i < HASH_TABLE_SIZE; i++){
        table->buckets[i] = NULL;
    }
    return table;
}