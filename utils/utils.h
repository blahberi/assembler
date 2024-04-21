//
// Author: Eitan H.
//

#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H

#include <stdbool.h>
#include <ctype.h>

bool is_number_signed(const char* str);
bool is_number_unsigned(const char* str);
void print_binary(unsigned int num, int bits);
char** split_string_by_comma(const char* str);
void trim_whitespace(char* str);

#endif //ASSEMBLER_UTILS_H
