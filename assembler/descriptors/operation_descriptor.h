/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_OPERATION_DESCRIPTOR_H
#define ASSEMBLER_OPERATION_DESCRIPTOR_H

#include "../enums.h"
#include "../handlers/handle_label.h"

struct Context;

typedef int InstructionGenerator(struct Context *context);

typedef struct OperationDescriptor {
    OPCODE opcode;
    InstructionGenerator* generate;
    LabelHandler *handle_label;
} OperationDescriptor;

OperationDescriptor* get_operation_descriptor(struct Context *context);

#endif /* ASSEMBLER_OPERATION_DESCRIPTOR_H */
