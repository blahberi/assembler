/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_DIRECTIVE_DESCRIPTOR_H
#define ASSEMBLER_DIRECTIVE_DESCRIPTOR_H

#include "../handlers/handle_label.h"
#include "../enums.h"


typedef struct directive_descriptor DirectiveDescriptor;

typedef int DirectiveGenerator(Context *context);

struct directive_descriptor {
    DIRECTIVE_TYPE type;
    DirectiveGenerator *generate;
    LabelHandler *handle_label;
};

DirectiveDescriptor* get_directive_descriptor(Context *context);

#endif /* ASSEMBLER_DIRECTIVE_DESCRIPTOR_H */
