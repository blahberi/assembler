//
// Author: Eitan H.
//

#ifndef ASSEMBLER_OPERAND_TO_MACHINE_CODE_H
#define ASSEMBLER_OPERAND_TO_MACHINE_CODE_H


#include "operand_descriptor.h"
#include "words.h"

int generate_immediate_operand(OperandDescriptor* descriptor, const AssemblerContext *context, Word* instruction_word);
int generate_direct_operand(OperandDescriptor* descriptor, const AssemblerContext *context, Word* instruction_word);
int generate_index_operand(OperandDescriptor* descriptor, const AssemblerContext *context, Word* instruction_word);
int generate_register_operand(OperandDescriptor* descriptor, const AssemblerContext *context, Word* instruction_word);

#endif //ASSEMBLER_OPERAND_TO_MACHINE_CODE_H
