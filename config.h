//
// Author: Eitan H.
//

#ifndef ASSEMBLER_CONFIG_H
#define ASSEMBLER_CONFIG_H

// Define constants
#define MEMORY_SIZE 4096

#define WORD_SIZE 14
#define ARE_SIZE 2
#define VALUE_SIZE 12
#define OPCODE_SIZE 4
#define ADDRESING_MODE_SIZE 2
#define REGISTER_SIZE 3


#define MAX_SIGNED_VALUE 2047
#define MIN_SIGNED_VALUE -2048
#define MAX_UNSIGNED_VALUE 4095

#define MAX_LARGE_SIGNED_VALUE 8191
#define MIN_LARGE_SIGNED_VALUE -8192
#define MAX_LARGE_UNSIGNED_VALUE 16383

#define MAX_LINE_LENGTH 80
#define MAX_LABEL_LENGTH 31

#define REGISTER_COUNT 8

#define SYMBOL_TABLE_SIZE 100

#endif //ASSEMBLER_CONFIG_H
