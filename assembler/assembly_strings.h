//
// Author: Eitan H.
//

#ifndef ASSEMBLER_ASSEMBLY_STRINGS_H
#define ASSEMBLER_ASSEMBLY_STRINGS_H


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

REGISTER_STATUS check_register(const char* operand);
LABEL_STATUS check_label(const char* label);
int parse_index_operand(const char* operand, char* address, char* index);
INDEX_OPERAND_STATUS check_index_operand(const char* operand);


#endif //ASSEMBLER_ASSEMBLY_STRINGS_H
