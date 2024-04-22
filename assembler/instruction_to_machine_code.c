//
// Author: Eitan H.
//

#include "instruction_to_machine_code.h"
#include "are.h"
#include "words.h"
#include "addressing_mode.h"

// Instruction generator utilities
void generate_first_word(const OperationDescriptor* descriptor, ADDR_MODE src, ADDR_MODE dest, AssemblerContext *context, Word *instruction_word) {
    // bits 0-1: ARE
    // bits 2-3: Destination addressing mode
    // bits 4-5: Source addressing mode
    // bits 6-9: Opcode

    int ic = context->IC;
    FirstWord *word = (FirstWord*)(instruction_word+ic);
    word->ARE = ABSOLUTE;
    word->DEST = dest;
    word->SRC = src;
    word->OPCODE = descriptor->opcode;
    context->IC++;
}

void generate_two_word_instruction(const OperationDescriptor* descriptor, OperandDescriptor* operands, AssemblerContext *context, Word *instruction_words) {
    OperandDescriptor *src = operands;
    OperandDescriptor *dest = operands+1;
    src->is_dest = false;
    dest->is_dest = true;
    generate_first_word(descriptor, src->addr_mode, dest->addr_mode, context, instruction_words);
    src->generate(src, context, instruction_words);
    if (src->addr_mode == REGISTER && dest->addr_mode == REGISTER) {
        context->IC--;
    }
    dest->generate(dest, context, instruction_words);
}

void generate_one_word_instruction(const OperationDescriptor* descriptor, OperandDescriptor* operands, AssemblerContext *context, Word *instruction_words) {
    OperandDescriptor *dest = &operands[0];
    dest->is_dest = true;
    generate_first_word(descriptor, 0, dest->addr_mode, context, instruction_words);
    dest->generate(dest, context, instruction_words);
}

void generate_zero_word_instruction(const OperationDescriptor* descriptor, OperandDescriptor* operands, AssemblerContext *context, Word *instruction_words) {
    generate_first_word(descriptor, 0, 0, context, instruction_words);
}