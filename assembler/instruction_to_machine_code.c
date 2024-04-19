//
// Author: Eitan H.
//

#include "instruction_to_machine_code.h"
#include "are.h"

typedef struct  {
    unsigned int ARE : 2;
    unsigned int DEST : 2; // Destination operand addressing mode
    unsigned int SRC : 2; // Source operand addressing mode
    unsigned int OPCODE : 4;
} FirstWord;

// Instruction generator utilities
void generate_first_word(OperationDescriptor* descriptor, ADDR_MODE src, ADDR_MODE dest, InstructionWord *instruction_word) {
    // bits 0-1: ARE
    // bits 2-3: Destination addressing mode
    // bits 4-5: Source addressing mode
    // bits 6-9: Opcode

    FirstWord *word = (FirstWord*)instruction_word;
    word->ARE = ABSOLUTE;
    word->DEST = dest;
    word->SRC = src;
    word->OPCODE = descriptor->opcode;
}

int generate_two_word_instruction(OperationDescriptor* descriptor, OperandDescriptor* operands, InstructionWord *instruction_words) {
    OperandDescriptor *src = &operands[0];
    OperandDescriptor *dest = &operands[1];
    get_addr_mode(src);
    get_addr_mode(dest);
    generate_first_word(descriptor, src->addr_mode, dest->addr_mode, instruction_words);
    int i = 1;
    i += src->generate(src, instruction_words+1);
    i += dest->generate(dest, instruction_words+i);
    return i;
}
