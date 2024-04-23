//
// Author: Eitan H.
//

#ifndef ASSEMBLER_LINE_DESCRIPTOR_H
#define ASSEMBLER_LINE_DESCRIPTOR_H

#include <stdbool.h>
#include "operand_descriptor.h"
#include "operation_descriptor.h"

typedef struct {
    char *line;
    const char *label;
    const char *sentence;
    const char *mnemonic;
    const char *operands;
    bool is_label;
} LineDescriptor;

typedef struct {
    LineDescriptor *line;
    OperationDescriptor *operation;
    OperandDescriptor *operands;
} InstructionLineDescriptor;

#endif //ASSEMBLER_LINE_DESCRIPTOR_H
