/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_OPERATION_DESCRIPTOR_H
#define ASSEMBLER_OPERATION_DESCRIPTOR_H

#include "../enums.h"
#include "../handlers/handle_label.h"

struct Context;

typedef int InstructionGenerator(struct Context *context);

typedef struct OperationDescriptor { /* Information about the operation */
    OPCODE opcode; /* The opcode */
    InstructionGenerator* generate; /* Function to generate the instruction */
    LabelHandler *handle_label; /* Function to handle a label */
} OperationDescriptor;

OperationDescriptor* get_operation_descriptor(struct Context *context); /* Get the operation descriptor */

#endif /* ASSEMBLER_OPERATION_DESCRIPTOR_H */
