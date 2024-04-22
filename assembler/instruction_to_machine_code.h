//
// Author: Eitan H.
//

#ifndef ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H
#define ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H

#include "assembler_context.h"
#include "words.h"
#include "operand_descriptor.h"
#include "operation_descriptor.h"


// Function prototypes
void generate_two_word_instruction(const OperationDescriptor*, OperandDescriptor*, AssemblerContext*, Word*);
void generate_one_word_instruction(const OperationDescriptor*, OperandDescriptor*, AssemblerContext*, Word*);
void generate_zero_word_instruction(const OperationDescriptor*, OperandDescriptor*, AssemblerContext*, Word*);

#endif //ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H
