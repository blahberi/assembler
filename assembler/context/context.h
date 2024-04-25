/*
 Author: Eitan H.
*/

#ifndef ASSERMBLER_CONTEXT_H
#define ASSERMBLER_CONTEXT_H

#include "assembler_context.h"
#include "../descriptors/line_descriptor.h"
#include "../descriptors/directive_descriptor.h"
#include "../descriptors/operand_descriptor.h"
#include "../descriptors/operation_descriptor.h"
#include "../words.h"

typedef struct Context { /* Context for the first and second pass */
    AssemblerContext* assembler_context; /* Assembler context */
    LineDescriptor* line_descriptor; /* Information about a line */
    InstructionLineDescriptor* instruction; /* Populate this if the line is an instruction */
    DirectiveDescriptor *directive; /* Populate this if the line is a directive */
    Word* instruction_words; /* Instruction machine code goes here */
    Word* data_words; /* Data machine code goes here */
} Context;

#endif /* ASSEMBLER_CONTEXT_H */