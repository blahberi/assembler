//
// Author: Eitan H.
//

#ifndef ASSEMBLER_ASSEMBLY_STRINGS_H
#define ASSEMBLER_ASSEMBLY_STRINGS_H

#include <stdbool.h>
#include "sentence_type.h"

extern const char* INSTRUCTIONS[];
extern const char* DIRECTIVES[];
const char* DEFINE;


typedef enum {
    INVALID_LABEL,
    INVALID_LABEL_LENGTH,
    VALID_LABEL
} LABEL_STATUS;

typedef enum {
    INVALID_OPERAND_LABEL,
    INVALID_OPERAND_LABEL_LENGTH,
    INVALID_OPERAND_INDEX,
    INVALID_OPERAND_INDEX_LENGTH,
    INVALID_OPERAND,
    VALID_OPERAND
} INDEX_OPERAND_STATUS;

typedef enum {
    VALID_REGISTER,
    INVALID_REGISTER_NAME,
    INVALID_REGISTER_ID
} REGISTER_STATUS;

bool is_instruction(const char* str);
REGISTER_STATUS check_register(const char* operand);
LABEL_STATUS check_label(const char* label);
int parse_index_operand(const char* operand, char* address, char* index);
INDEX_OPERAND_STATUS check_index_operand(const char* operand);
bool is_label_in_line(const char* line);
void split_label_and_sentence(const char* line, char* label, char* sentence);
char* get_sentence_start(const char* sentence);
SENTENCE_TYPE get_sentence_type(const char* sentence);
char* get_operands(const char* sentence);

#endif //ASSEMBLER_ASSEMBLY_STRINGS_H
