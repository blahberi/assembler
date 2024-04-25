/*
 Author: Eitan H.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../errors.h"
#include "memory_allocator.h"

typedef struct MemoryNode {
    void* data;
    struct MemoryNode* next;
} MemoryNode;

typedef struct StackNode {
    MemoryNode* memory_node;
    struct StackNode* next;
} StackNode;

StackNode *stack;
StackNode *global;

void init_memory() {
    stack = malloc(sizeof(StackNode));
    if (stack == NULL) {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
        exit(EXIT_FAILURE);
    }
    global = stack;
    stack->memory_node = NULL;
    stack->next = NULL;
}

void pop_memory() {
    MemoryNode* node = stack->memory_node;
    StackNode* stack_next;
    MemoryNode* next;
    while (node != NULL) {
        next = node->next;
        free(node->data);
        free(node);
        node = next;
    }
    stack_next = stack->next;
    free(stack);
    stack = stack_next;
}

void free_all_memory() {
    while (stack != NULL) {
        pop_memory();
    }
}

void push_memory() {
    StackNode* new_node = malloc(sizeof(StackNode));
    if (new_node == NULL) {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
        free_all_memory();
        exit(EXIT_FAILURE);
    }
    new_node->memory_node = NULL;
    new_node->next = stack;
    stack = new_node;
}

static void* allocate_helper(void* data, StackNode *stack_node) {
    MemoryNode* node;
    if (data != NULL) {
        node = malloc(sizeof(MemoryNode));
        if (node != NULL) {
            node->data = data;
            node->next = stack_node->memory_node;
            stack_node->memory_node = node;
            return data;
        }
        free(data);
        fprintf(stderr, ERR_FAILED_TO_TRACK_MEMORY);

    }
    else {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
    }
    free_all_memory();
    exit(EXIT_FAILURE);
}

void* malloc_track(size_t size) {
    void* data = malloc(size);
    return allocate_helper(data, stack);
}

void* calloc_track(size_t num, size_t size) {
    void* data = calloc(num, size);
    return allocate_helper(data, stack);
}

void track_pointer(void* ptr) {
    allocate_helper(ptr, stack);
}

void* malloc_track_global(size_t size) {
    void* data = malloc(size);
    return allocate_helper(data, global);
}

void* calloc_track_global(size_t num, size_t size) {
    void* data = calloc(num, size);
    return allocate_helper(data, global);
}

void track_pointer_global(void* ptr) {
    allocate_helper(ptr, global);
}