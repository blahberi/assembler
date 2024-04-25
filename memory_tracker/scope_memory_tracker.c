//
// Author: Eitan H.
//

#include <stdio.h>
#include <stdlib.h>
#include "../errors.h"
#include "global_memory_tracker.h"

typedef struct MemoryNode {
    void* data;
    struct MemoryNode* next;
} MemoryNode;

typedef struct StackNode {
    MemoryNode* memory_node;
    struct StackNode* next;
} StackNode;

StackNode *stack = NULL;

void init_memory_stack() {
    stack = malloc(sizeof(StackNode));
    if (stack == NULL) {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
        exit(EXIT_FAILURE);
    }
    stack->memory_node = NULL;
    stack->next = NULL;
}

void pop_memory_stack() {
    MemoryNode* node = stack->memory_node;
    while (node != NULL) {
        MemoryNode* next = node->next;
        free(node->data);
        free(node);
        node = next;
    }
    StackNode* next = stack->next;
    free(stack);
    stack = next;
}

void free_all_memory_stack() {
    while (stack != NULL) {
        pop_memory_stack();
    }
}

void increment_memory_stack() {
    StackNode* new_node = malloc(sizeof(StackNode));
    if (new_node == NULL) {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
        free_all_memory_stack();
        free_all_global_memory();
        exit(EXIT_FAILURE);
    }
    new_node->memory_node = NULL;
    new_node->next = stack;
    stack = new_node;
}

static void* allocate_helper(void* data) {
    if (data != NULL) {
        MemoryNode * node = malloc(sizeof(MemoryNode));
        if (node != NULL) {
            node->data = data;
            node->next = stack->memory_node;
            stack->memory_node = node;
            return data;
        }
        free(data);
        fprintf(stderr, ERR_FAILED_TO_TRACK_MEMORY);

    }
    else {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
    }
    free_all_memory_stack();
    free_all_global_memory();
    exit(EXIT_FAILURE);
}

void* malloc_track(size_t size) {
    void* data = malloc(size);
    return allocate_helper(data);
}

void* calloc_track(size_t num, size_t size) {
    void* data = calloc(num, size);
    return allocate_helper(data);
}

void track_pointer(void* ptr) {
    allocate_helper(ptr);
}