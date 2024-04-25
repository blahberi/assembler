/*
Author: Eitan H.
*/

#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H

#include <stdbool.h>
#include <ctype.h>

char* get_preprocessed_filepath(const char* filepath);
char* get_extern_filepath(const char* filepath);
char* get_entry_filepath(const char* filepath);
char* get_output_filepath(const char* filepath);
bool is_valid_filepath(const char* filepath);

#endif /* ASSEMBLER_UTILS_H */
