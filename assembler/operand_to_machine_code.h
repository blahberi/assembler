/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_OPERAND_TO_MACHINE_CODE_H
#define ASSEMBLER_OPERAND_TO_MACHINE_CODE_H

#include "descriptors/operand_descriptor.h"

int generate_immediate_operand(OperandDescriptor* descriptor, Context *context); /* Generate machine code for an immediate operand */
int generate_direct_operand(OperandDescriptor* descriptor, Context *context); /* Generate machine code for a direct operand */
int generate_index_operand(OperandDescriptor* descriptor, Context *context); /* Generate machine code for an index operand */
int generate_register_operand(OperandDescriptor* descriptor, Context *context); /* Generate machine code for a register operand */

#endif /* ASSEMBLER_OPERAND_TO_MACHINE_CODE_H */
