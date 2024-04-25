//
// Author: Eitan H.
//

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "../errors.h"
#include "scope_memory_tracker.c.h"

typedef struct MemoryNode {
    void* data;
    struct MemoryNode* next;
} MemoryNode;

MemoryNode *head = NULL;

void free_all_global_memory() {
    MemoryNode* node = head;
    while (node != NULL) {
        MemoryNode* next = node->next;
        free(node->data);
        free(node);
        node = next;
    }
}

static void* allocate_helper(void* data) {
    if (data != NULL) {
        MemoryNode * node = malloc(sizeof(MemoryNode));
        if (node != NULL) {
            node->data = data;
            node->next = head;
            head = node;
            return data;
        }
        free(data);
        fprintf(stderr, ERR_FAILED_TO_TRACK_MEMORY);

    }
    else {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
    }
    free_all_memory_stack();
    exit(EXIT_FAILURE);
}

void* malloc_track_global(size_t size) {
    void* data = malloc(size);
    return allocate_helper(data);
}

void* calloc_track_global(size_t num, size_t size) {
    void* data = calloc(num, size);
    return allocate_helper(data);
}

void track_pointer_global(void* ptr) {
    allocate_helper(ptr);
}