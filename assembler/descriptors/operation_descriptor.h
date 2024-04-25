//
// Author: Eitan H.
//

#ifndef ASSEMBLER_OPERATION_DESCRIPTOR_H
#define ASSEMBLER_OPERATION_DESCRIPTOR_H

#include "../enums.h"
#include "../handlers/handle_label.h"

typedef struct context Context;

typedef struct operation_descriptor OperationDescriptor;

typedef int InstructionGenerator(Context *context);

struct operation_descriptor {
    OPCODE opcode;
    InstructionGenerator* generate;
    LabelHandler *handle_label;
};

OperationDescriptor* get_operation_descriptor(Context *context);

#endif //ASSEMBLER_OPERATION_DESCRIPTOR_H
