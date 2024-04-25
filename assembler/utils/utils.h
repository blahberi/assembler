/*
Author: Eitan H.
*/

#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H

#include <stdbool.h>
#include <ctype.h>

char* my_strdup(const char* str); /* Similar to POSIX strdup, but uses custom memory allocator */
char* my_strdup_global(const char* str); /* Similar to POSIX strdup, but uses the custom global memory allocator */
char* get_preprocessed_filepath(const char* filepath); /* Get the preprocessed file path */
char* get_extern_filepath(const char* filepath); /* Get the extern file path */
char* get_entry_filepath(const char* filepath); /* Get the entry file path */
char* get_output_filepath(const char* filepath); /* Get the output file path */

#endif /* ASSEMBLER_UTILS_H */
