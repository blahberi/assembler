//
// Author: Eitan H.
//

#ifndef ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H
#define ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H

#include <stdint.h>
#include "../symbol_table/table/symbol_table.h" // Assuming the symbol table is defined here
#include "../descriptors/operation_descriptor.h"

// Function prototypes
int generate_two_word_instruction(OperationDescriptor*, OperandDescriptor*, OperandDescriptor*, InstructionWord*);

#endif //ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H
