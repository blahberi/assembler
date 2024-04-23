//
// Author: Eitan H.
//

#ifndef ASSEMBLER_DIRECTIVE_TO_MACHINE_CODE_H
#define ASSEMBLER_DIRECTIVE_TO_MACHINE_CODE_H

#include "descriptors/directive_descriptor.h"

int generate_data_directive(const DirectiveDescriptor*, const char*, const char*, AssemblerContext*, Word*);
int generate_string_directive(const DirectiveDescriptor*, const char*, const char*, AssemblerContext*, Word*);
int generate_entry_directive(const DirectiveDescriptor*, const char*, const char*, AssemblerContext*, Word*);
int generate_extern_directive(const DirectiveDescriptor*, const char*, const char*, AssemblerContext*, Word*);

#endif //ASSEMBLER_DIRECTIVE_TO_MACHINE_CODE_H
