//
// Author: Eitan H.
//

#ifndef ASSEMBLER_GLOBAL_MEMORY_TRACKER_H
#define ASSEMBLER_GLOBAL_MEMORY_TRACKER_H

void free_all_global_memory();
void* malloc_track_global(size_t size);
void* calloc_track_global(size_t num, size_t size);
void track_pointer_global(void* ptr);

#endif //ASSEMBLER_GLOBAL_MEMORY_TRACKER_H
