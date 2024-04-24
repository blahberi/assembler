//
// Author: Eitan H.
//

#ifndef ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H
#define ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H

typedef struct context Context;

// Function prototypes
int generate_two_word_instruction(Context *context);
int generate_one_word_instruction(Context *context);
int generate_zero_word_instruction(Context *context);

#endif //ASSEMBLER_INSTRUCTION_TO_MACHINE_CODE_H
