/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_DIRECTIVE_DESCRIPTOR_H
#define ASSEMBLER_DIRECTIVE_DESCRIPTOR_H

#include "../handlers/handle_label.h"
#include "../enums.h"


typedef struct DirectiveDescriptor DirectiveDescriptor;
struct Context;

typedef int DirectiveGenerator(struct Context *context); /* Function pointer for generating directive machine code */

struct DirectiveDescriptor { /* Information about a directive */
    DIRECTIVE_TYPE type; /* Directive type */
    DirectiveGenerator *generate; /* Function for generating machine code */
    LabelHandler *handle_label; /* Function for handling labels */
};

DirectiveDescriptor* get_directive_descriptor(struct Context *context);

#endif /* ASSEMBLER_DIRECTIVE_DESCRIPTOR_H */
