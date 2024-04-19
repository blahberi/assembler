//
// Author: Eitan H.
//

#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H

#include <stdbool.h>
#include <ctype.h>

bool is_number_signed(const char* str);
bool is_number_unsigned(const char* str);
bool is_register(const char* operand);

#endif //ASSEMBLER_UTILS_H
