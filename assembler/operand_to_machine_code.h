/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_OPERAND_TO_MACHINE_CODE_H
#define ASSEMBLER_OPERAND_TO_MACHINE_CODE_H

#include "descriptors/operand_descriptor.h"

int generate_immediate_operand(OperandDescriptor* descriptor, Context *context);
int generate_direct_operand(OperandDescriptor* descriptor, Context *context);
int generate_index_operand(OperandDescriptor* descriptor, Context *context);
int generate_register_operand(OperandDescriptor* descriptor, Context *context);

#endif /* ASSEMBLER_OPERAND_TO_MACHINE_CODE_H */
