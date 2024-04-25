/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_MEMORY_ALLOCATOR_H
#define ASSEMBLER_MEMORY_ALLOCATOR_H

#include <stdlib.h>

void init_memory();
void pop_memory();
void free_all_memory();
void push_memory();

void* malloc_track(size_t size);
void* calloc_track(size_t num, size_t size);
void track_pointer(void* ptr);

void* malloc_track_global(size_t size);
void* calloc_track_global(size_t num, size_t size);
void track_pointer_global(void* ptr);


#endif /* ASSEMBLER_MEMORY_ALLOCATOR_H */
