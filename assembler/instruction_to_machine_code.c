//
// Author: Eitan H.
//

#include "instruction_to_machine_code.h"
#include "are.h"
#include "words.h"
#include "addressing_mode.h"

// Instruction generator utilities
int generate_first_word(const OperationDescriptor* descriptor, ADDR_MODE src, ADDR_MODE dest, AssemblerContext *context, Word *instruction_word) {
    // bits 0-1: ARE
    // bits 2-3: Destination addressing mode
    // bits 4-5: Source addressing mode
    // bits 6-9: Opcode
    if (!context->is_first_pass) {
        context->IC++;
        return 0;
    }

    int ic = context->IC;
    FirstWord *word = (FirstWord*)(instruction_word+ic);
    word->ARE = ABSOLUTE;
    word->DEST = dest;
    word->SRC = src;
    word->OPCODE = descriptor->opcode;
    context->IC++;
    return 0;
}

int generate_two_word_instruction(const OperationDescriptor* descriptor, OperandDescriptor* operands, const char* line, AssemblerContext *context, Word *instruction_words) {
    OperandDescriptor *src = operands;
    OperandDescriptor *dest = operands+1;
    src->is_dest = false;
    dest->is_dest = true;
    int res1 = generate_first_word(descriptor, src->addr_mode, dest->addr_mode, context, instruction_words);
    src->generate(src, line, context, instruction_words);
    if (src->addr_mode == REGISTER && dest->addr_mode == REGISTER) {
        context->IC--;
    }
    int res2 = dest->generate(dest, line, context, instruction_words);

    if (res1 != 0 || res2 != 0) {
        return -1;
    }
}

int generate_one_word_instruction(const OperationDescriptor* descriptor, OperandDescriptor* operands, const char* line, AssemblerContext *context, Word *instruction_words) {
    OperandDescriptor *dest = &operands[0];
    dest->is_dest = true;
    int res1 = generate_first_word(descriptor, 0, dest->addr_mode, context, instruction_words);
    int res2 = dest->generate(dest, line, context, instruction_words);
    if (res1 != 0 || res2 != 0) {
        return -1;
    }
}

int generate_zero_word_instruction(const OperationDescriptor* descriptor, OperandDescriptor* operands, const char* line, AssemblerContext *context, Word *instruction_words) {
    return generate_first_word(descriptor, 0, 0, context, instruction_words);
}