/*
 Author: Eitan H.
*/

#include "descriptors/operation_descriptor.h"

#ifndef ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H
#define ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H

/* Function prototypes */
int generate_two_word_instruction(Context *context); /* For instructions with two operands */
int generate_one_word_instruction(Context *context); /* For instructions with one operand */
int generate_zero_word_instruction(Context *context); /* For instructions with no operands */

int (*get_instruction_generator(OPCODE opcode))(Context*); /* Returns the appropriate instruction generator function for a given operation */

#endif /* ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H */
