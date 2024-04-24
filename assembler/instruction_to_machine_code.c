//
// Author: Eitan H.
//


#include "context/context.h"
#include "are.h"

// Instruction generator utilities
int generate_first_word(Context *context) {
    // bits 0-1: ARE
    // bits 2-3: Destination addressing mode
    // bits 4-5: Source addressing mode
    // bits 6-9: Opcode

    bool is_first_pass = context->assembler_context->is_first_pass;
    Word *instruction_word = context->instruction_words;
    int *IC = &context->assembler_context->IC;
    if (!is_first_pass) {
        (*IC)++;

        return 0;
    }

    OperationDescriptor *descriptor = context->instruction->operation;
    OperandDescriptor *operands = context->instruction->operands;

    ADDR_MODE dest = operands[0].addr_mode;
    ADDR_MODE src = operands[1].addr_mode;

    int ic = *IC;
    FirstWord *word = (FirstWord*)(instruction_word+ic);
    word->ARE = ABSOLUTE;
    word->DEST = dest;
    word->SRC = src;
    word->OPCODE = descriptor->opcode;
    (*IC)++;
    return 0;
}

int generate_two_word_instruction(Context *context) {
    OperandDescriptor *operands = context->instruction->operands;
    OperandDescriptor *src = operands;
    OperandDescriptor *dest = operands+1;
    int *IC = &context->assembler_context->IC;
    src->is_dest = false;
    dest->is_dest = true;
    int res1 = generate_first_word(context);
    src->generate(src, context);
    if (src->addr_mode == REGISTER && dest->addr_mode == REGISTER) {
        (*IC)--;
    }
    int res2 = dest->generate(dest, context);

    if (res1 != 0 || res2 != 0) {
        return -1;
    }
}

int generate_one_word_instruction(Context *context) {
    OperandDescriptor *operands = context->instruction->operands;
    OperandDescriptor *dest = operands;
    dest->is_dest = true;
    int res1 = generate_first_word(context);
    int res2 = dest->generate(dest, context);
    if (res1 != 0 || res2 != 0) {
        return -1;
    }
}

int generate_zero_word_instruction(Context *context) {
    return generate_first_word(context);
}