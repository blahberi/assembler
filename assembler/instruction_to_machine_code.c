//
// Author: Eitan H.
//

#include "instruction_to_machine_code.h"
#include "are.h"
#include "words.h"

// Instruction generator utilities
void generate_first_word(const OperationDescriptor* descriptor, ADDR_MODE src, ADDR_MODE dest, Word *instruction_word) {
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

int generate_two_word_instruction(const OperationDescriptor* descriptor, OperandDescriptor* operands, AssemblerContext *context, Word *instruction_words) {
    OperandDescriptor *src = &operands[0];
    OperandDescriptor *dest = &operands[1];
    src->is_dest = false;
    dest->is_dest = true;
    get_addr_mode(src, context);
    get_addr_mode(dest, context);
    generate_first_word(descriptor, src->addr_mode, dest->addr_mode, instruction_words);
    int i = 1;
    i += src->generate(src, context, instruction_words+1);
    if (src->addr_mode == REGISTER && dest->addr_mode == REGISTER) {
        i--;
    }
    i += dest->generate(dest, context, instruction_words+i);

    context->IC += i;
    return i;
}
