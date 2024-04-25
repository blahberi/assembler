/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_LINE_DESCRIPTOR_H
#define ASSEMBLER_LINE_DESCRIPTOR_H

#include <stdbool.h>

struct OperationDescriptor;
struct OperandDescriptor;

typedef struct instruction_line_descriptor {
    struct OperationDescriptor *operation;
    struct OperandDescriptor *operands;
    int operand_count;
} InstructionLineDescriptor;


typedef struct line_descriptor {
    char *line;
    char *label;
    char *sentence;
    char *mnemonic;
    char *operands;
    bool is_label;
} LineDescriptor;

#endif /* ASSEMBLER_LINE_DESCRIPTOR_H */
