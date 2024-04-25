/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_MEMORY_ALLOCATOR_H
#define ASSEMBLER_MEMORY_ALLOCATOR_H

#include <stdlib.h>

void init_memory(); /* Initialize the memory allocator */
void pop_memory(); /* Pop the last memory block */
void free_all_memory(); /* Free all memory */
void push_memory(); /* Push a new memory block */

void* malloc_track(size_t size); /* malloc and add it to current memory block to track it */
void* calloc_track(size_t num, size_t size);  /* calloc and add it to current memory block to track it */
void track_pointer(void* ptr); /* Add a pointer to the current memory block to track it */

void* malloc_track_global(size_t size); /* malloc and add it to global memory block to track it */
void* calloc_track_global(size_t num, size_t size); /* calloc and add it to global memory block to track it */
void track_pointer_global(void* ptr); /* Add a pointer to the global memory block to track it */


#endif /* ASSEMBLER_MEMORY_ALLOCATOR_H */
