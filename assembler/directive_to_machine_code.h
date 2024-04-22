//
// Author: Eitan H.
//

#ifndef ASSEMBLER_DIRECTIVE_TO_MACHINE_CODE_H
#define ASSEMBLER_DIRECTIVE_TO_MACHINE_CODE_H

#include "directive_descriptor.h"

void generate_data_directive(const DirectiveDescriptor*, const char*, AssemblerContext*, Word*);
void generate_string_directive(const DirectiveDescriptor*, const char*, AssemblerContext*, Word*);
void generate_entry_directive(const DirectiveDescriptor*, const char*, AssemblerContext*, Word*);
void generate_extern_directive(const DirectiveDescriptor*, const char*, AssemblerContext*, Word*);

#endif //ASSEMBLER_DIRECTIVE_TO_MACHINE_CODE_H
