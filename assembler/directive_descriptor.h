//
// Author: Eitan H.
//

#ifndef ASSEMBLER_DIRECTIVE_DESCRIPTOR_H
#define ASSEMBLER_DIRECTIVE_DESCRIPTOR_H

#include "operand_descriptor.h"
#include "handle_label.h"

typedef enum {
    DATA,
    STRING,
    ENTRY,
    EXTERN

} DIRECTIVE_TYPE;

typedef struct directive_descriptor DirectiveDescriptor;

typedef int DirectiveGenerator(const DirectiveDescriptor*, const char*, AssemblerContext*, Word*);

struct directive_descriptor {
    DIRECTIVE_TYPE type;
    DirectiveGenerator *generate;
    LabelHandler *handle_label;
};

DirectiveDescriptor* get_directive_descriptor(const char* sentance);

#endif //ASSEMBLER_DIRECTIVE_DESCRIPTOR_H
