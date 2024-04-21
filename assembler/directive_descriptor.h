//
// Author: Eitan H.
//

#ifndef ASSEMBLER_DIRECTIVE_DESCRIPTOR_H
#define ASSEMBLER_DIRECTIVE_DESCRIPTOR_H

#include "operand_descriptor.h"

typedef enum {
    DATA,
    STRING,
    ENTRY,
    EXTERN

} DIRECTIVE_TYPE;

typedef struct directive_descriptor DirectiveDescriptor;

typedef int DirectiveGenerator(const DirectiveDescriptor*, OperandDescriptor*, const AssemblerContext*, Word*);

struct OperationDescriptor {
    DIRECTIVE_TYPE opcode;
    DirectiveGenerator *generate;
};


#endif //ASSEMBLER_DIRECTIVE_DESCRIPTOR_H
