/*
 Author: Eitan H.

 * This module is responsible for handling all the memory allocations in the program.
 * We use a stack of memory lists to keep track of all the memory we allocate.
 * When entering a new scope, we push a new memory list to the stack and all the memory we allocate in that scope is tracked in that list.
 * When exiting a scope, we pop the top memory list from the stack and free all the memory in that list.
 *
 * The bottom of the stack is the global memory list, which is used to track memory that is not in a specific scope.
 * Such memory could be symbols in the symbol table, etc.
 * We have the ability to add to the global memory list from any scope.
 *
 * We also have the ability to remove all the memory we allocated in the program.
 * This is useful for freeing all the memory we allocated in case of an error or when the program ends.
 *
 * We also have the ability to track a pointer that was allocated outside of the memory allocator
 * by either adding it to the current memory list or the global memory list.
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

void init_memory() { /* Initialize the memory allocator */
    stack = malloc(sizeof(StackNode));
    if (stack == NULL) {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
        exit(EXIT_FAILURE);
    }
    global = stack;
    stack->memory_node = NULL;
    stack->next = NULL;
}

void pop_memory() { /* Pop the top memory stack */
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

void free_all_memory() { /* Free all memory */
    while (stack != NULL) {
        pop_memory();
    }
}

void push_memory() { /* Push a new memory stack */
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

void* malloc_track(size_t size) { /* Allocate memory with malloc and track it */
    void* data = malloc(size);
    return allocate_helper(data, stack);
}

void* calloc_track(size_t num, size_t size) { /* Allocate memory with calloc and track it */
    void* data = calloc(num, size);
    return allocate_helper(data, stack);
}

void track_pointer(void* ptr) { /* Track a pointer */
    allocate_helper(ptr, stack);
}

void* malloc_track_global(size_t size) { /* Allocate memory with malloc and track it in the global memory list */
    void* data = malloc(size);
    return allocate_helper(data, global);
}

void* calloc_track_global(size_t num, size_t size) { /* Allocate memory with calloc and track it in the global memory list */
    void* data = calloc(num, size);
    return allocate_helper(data, global);
}

void track_pointer_global(void* ptr) { /* Track a pointer in the global memory list */
    allocate_helper(ptr, global);
}