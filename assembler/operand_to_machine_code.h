//
// Author: Eitan H.
//

#ifndef ASSEMBLER_OPERAND_TO_MACHINE_CODE_H
#define ASSEMBLER_OPERAND_TO_MACHINE_CODE_H


#include "operand_descriptor.h"
#include "words.h"

void generate_immediate_operand(OperandDescriptor* descriptor, AssemblerContext *context, Word* instruction_word);
void generate_direct_operand(OperandDescriptor* descriptor, AssemblerContext *context, Word* instruction_word);
void generate_index_operand(OperandDescriptor* descriptor, AssemblerContext *context, Word* instruction_word);
void generate_register_operand(OperandDescriptor* descriptor, AssemblerContext *context, Word* instruction_word);

#endif //ASSEMBLER_OPERAND_TO_MACHINE_CODE_H
