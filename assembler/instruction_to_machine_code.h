//
// Author: Eitan H.
//

#ifndef ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H
#define ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H

#include "assembler_context.h"
#include "words.h"
#include "descriptors/operand_descriptor.h"
#include "descriptors/operation_descriptor.h"


// Function prototypes
int generate_two_word_instruction(const OperationDescriptor*, OperandDescriptor*, const char* line, AssemblerContext*, Word*);
int generate_one_word_instruction(const OperationDescriptor*, OperandDescriptor*, const char* line, AssemblerContext*, Word*);
int generate_zero_word_instruction(const OperationDescriptor*, OperandDescriptor*, const char* line, AssemblerContext*, Word*);

#endif //ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H
