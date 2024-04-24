//
// Author: Eitan H.
//


#include "assembler_context.h"
#include "../descriptors/line_descriptor.h"
#include "../descriptors/directive_descriptor.h"
#include "../descriptors/operand_descriptor.h"
#include "../descriptors/operation_descriptor.h"
#include "../words.h"

typedef struct context {
    AssemblerContext* assembler_context;
    LineDescriptor* line_descriptor;
    InstructionLineDescriptor* instruction;
    DirectiveDescriptor *directive;
    Word* instruction_words;
    Word* data_words;
} Context;