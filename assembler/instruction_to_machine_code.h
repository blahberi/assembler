//
// Author: Eitan H.
//

#ifndef ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H
#define ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H

#include <stdint.h>
#include "../symbol_table/symbol_table.h" // Assuming the symbol table is defined here
#include "operation_descriptor.h"
#include "words.h"

// Function prototypes
int generate_two_word_instruction(const OperationDescriptor*, OperandDescriptor*, AssemblerContext*, Word*);

#endif //ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H
