//
// Author: Eitan H.
//

#ifndef ASSEMBLER_LINE_DESCRIPTOR_H
#define ASSEMBLER_LINE_DESCRIPTOR_H

#include <stdbool.h>

typedef struct operation_descriptor OperationDescriptor;
typedef struct operand_descriptor OperandDescriptor;

typedef struct instruction_line_descriptor {
    OperationDescriptor *operation;
    OperandDescriptor *operands;
} InstructionLineDescriptor;


typedef struct line_descriptor {
    char *line;
    char *label;
    char *sentence;
    char *mnemonic;
    char *operands;
    bool is_label;
} LineDescriptor;

#endif //ASSEMBLER_LINE_DESCRIPTOR_H
