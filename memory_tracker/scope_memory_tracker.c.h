//
// Author: Eitan H.
//

#ifndef ASSEMBLER_SCOPE_MEMORY_TRACKER_C_H
#define ASSEMBLER_SCOPE_MEMORY_TRACKER_C_H

void init_memory_stack();
void pop_memory_stack();
void free_all_memory_stack();
void increment_memory_stack();
void* malloc_track(size_t size);
void* calloc_track(size_t num, size_t size);
void track_pointer(void* pointer);

#endif //ASSEMBLER_SCOPE_MEMORY_TRACKER_C_H
