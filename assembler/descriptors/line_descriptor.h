/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_LINE_DESCRIPTOR_H
#define ASSEMBLER_LINE_DESCRIPTOR_H

#include <stdbool.h>

struct OperationDescriptor;
struct OperandDescriptor;

typedef struct InstructionLineDescriptor { /* Information about an instruction line */
    struct OperationDescriptor *operation; /* Operation descriptor */
    struct OperandDescriptor *operands; /* Operands descriptors */
    int operand_count; /* Number of operands */
} InstructionLineDescriptor;


typedef struct line_descriptor { /* Information about a line */
    char *line; /* The line */
    char *label; /* The label */
    char *sentence; /* The sentence (the line without the label) */
    char *mnemonic; /* The mnemonic (instruction or directive, "mov", ".data", etc) */
    char *operands; /* The operands */
    bool is_label; /* Is there a label? */
} LineDescriptor;

#endif /* ASSEMBLER_LINE_DESCRIPTOR_H */
