//
// Author: Eitan H.
//


#include <stdio.h>
#include "context/context.h"
#include "../errors.h"
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

    ADDR_MODE dest = 0;
    ADDR_MODE src = 0;
    int operand_count = context->instruction->operand_count;
    if (operand_count == 1) {
        dest = operands[0].addr_mode;
    } else if (operand_count == 2) {
        dest = operands[1].addr_mode;
        src = operands[0].addr_mode;
    }

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
    generate_first_word(context);
    int res1 = src->generate(src, context);
    if (src->addr_mode == REGISTER && dest->addr_mode == REGISTER) {
        (*IC)--;
    }
    int res2 = dest->generate(dest, context);

    if (res1 != 0 || res2 != 0) {
        goto error;
    }
    return 0;

    error:
    return -1;
}

int generate_one_word_instruction(Context *context) {
    OperandDescriptor *operands = context->instruction->operands;
    OperandDescriptor *dest = operands;
    dest->is_dest = true;
    int res1 = generate_first_word(context);
    int res2 = dest->generate(dest, context);
    if (res1 != 0 || res2 != 0) {
        goto error;
    }

    return 0;

    error:
    return -1;
}

int generate_zero_word_instruction(Context *context) {
    return generate_first_word(context);
}

int generate_type_1(Context *context) { // mov, add, sub
    // src operand: Immediate, Direct, Index, Register
    // dest operand: Direct, Index, Register

    bool is_first_pass = context->assembler_context->is_first_pass;
    const char *line = context->line_descriptor->line;
    int operand_count = context->instruction->operand_count;

    if (operand_count != 2) {
        if (is_first_pass){
            fprintf(stderr, ERR_EXPECTED_TWO_OPERANDS, line);
        }
        goto error;
    }

    OperandDescriptor dest = context->instruction->operands[1];

    if (dest.addr_mode == IMMEDIATE) {
        if (is_first_pass) {
            fprintf(stderr, ERR_DEST_CANNOT_BE_IMMEDIATE, line);
        }
        goto error;
    }
    return generate_two_word_instruction(context);

    error:
    return -1;
}

int generate_type_2(Context *context) {  // cmp
    // src operand: Immediate, Direct, Index, Register
    // dest operand: Immediate, Direct, Index, Register

    bool is_first_pass = context->assembler_context->is_first_pass;
    char *line = context->line_descriptor->line;
    int operand_count = context->instruction->operand_count;

    if (operand_count != 2) {
        if (is_first_pass) {
            fprintf(stderr, ERR_EXPECTED_TWO_OPERANDS, line);
        }
        goto error;
    }
    return generate_two_word_instruction(context);

    error:
    return -1;
}

int generate_type_3(Context *context) { // not, clr, inc, dec, red
    // no src operand
    // dest operand: Direct, Index, Register

    bool is_first_pass = context->assembler_context->is_first_pass;
    const char *line = context->line_descriptor->line;
    int operand_count = context->instruction->operand_count;

    if (operand_count != 1) {
        if (is_first_pass) {
            fprintf(stderr, ERR_EXPECTED_ONE_OPERAND, line);
        }
        goto error;
    }

    OperandDescriptor dest = context->instruction->operands[0];

    if (dest.addr_mode == IMMEDIATE) {
        if (is_first_pass) {
            fprintf(stderr, ERR_DEST_CANNOT_BE_IMMEDIATE, line);
        }
        goto error;
    }

    return generate_one_word_instruction(context);

    error:
    return -1;
}

int generate_type_4(Context *context) { // lea
    // src operand: Direct, Index
    // dest operand: Direct, Index, Register

    bool is_first_pass = context->assembler_context->is_first_pass;
    const char *line = context->line_descriptor->line;
    int operand_count = context->instruction->operand_count;

    if (operand_count != 2) {
        if (is_first_pass) {
            fprintf(stderr, ERR_EXPECTED_TWO_OPERANDS, line);
        }
        goto error;
    }

    OperandDescriptor src = context->instruction->operands[0];
    OperandDescriptor dest = context->instruction->operands[1];

    if (src.addr_mode == IMMEDIATE) {
        if (is_first_pass) {
            fprintf(stderr, ERR_SRC_CANNOT_BE_IMMEDIATE, line);
        }
        goto error;
    }
    if (src.addr_mode == REGISTER) {
        if (is_first_pass) {
            fprintf(stderr, ERR_SRC_CANNOT_BE_REGISTER, line);
        }
        goto error;
    }

    if (dest.addr_mode == IMMEDIATE) {
        if (is_first_pass) {
            fprintf(stderr, ERR_DEST_CANNOT_BE_IMMEDIATE, line);
        }
        goto error;
    }

    return generate_two_word_instruction(context);

    error:
    return -1;
}

int generate_type_5(Context *context) { // jmp, bne, jsr
    // no src operand
    // dest operand: Direct, Register
    bool is_first_pass = context->assembler_context->is_first_pass;
    const char *line = context->line_descriptor->line;
    int operand_count = context->instruction->operand_count;

    if (operand_count != 1) {
        if (is_first_pass) {
            fprintf(stderr, ERR_EXPECTED_ONE_OPERAND, line);
        }
        goto error;
    }

    OperandDescriptor dest = context->instruction->operands[0];

    if (dest.addr_mode == IMMEDIATE) {
        if (is_first_pass) {
            fprintf(stderr, ERR_DEST_CANNOT_BE_IMMEDIATE, line);
        }
        goto error;
    }
    if (dest.addr_mode == INDEX) {
        if (is_first_pass) {
            fprintf(stderr, ERR_DEST_CANNOT_BE_INDEX, line);
        }
        goto error;
    }

    return generate_one_word_instruction(context);

    error:
    return -1;
}

int generate_type_6(Context *context) { // prn
    // no src operand
    // dest operand: Immediate, Direct, Index, Register

    bool is_first_pass = context->assembler_context->is_first_pass;
    const char* line = context->line_descriptor->line;
    int operand_count = context->instruction->operand_count;

    if (operand_count != 1) {
        if (is_first_pass) {
            fprintf(stderr, ERR_EXPECTED_ONE_OPERAND, line);
        }
        goto error;
    }

    return generate_one_word_instruction(context);

    error:
    return -1;
}

int generate_type_7(Context *context) { // rts, hlt
    // no src operand
    // no dest operand

    bool is_first_pass = context->assembler_context->is_first_pass;
    const char *line = context->line_descriptor->line;
    int operand_count = context->instruction->operand_count;

    if (operand_count != 0) {
        if (is_first_pass) {
            fprintf(stderr, ERR_EXPECTED_ZERO_OPERANDS, line);
        }
        goto error;
    }

    return generate_zero_word_instruction(context);

    error:
    return -1;
}

int (*get_instruction_generator(OPCODE opcode))(Context*){ // Get the generator function given the opcode
    int (*generator_functions[])(Context*) = {
            [MOV] = generate_type_1,
            [ADD] = generate_type_1,
            [SUB] = generate_type_1,
            [CMP] = generate_type_2,
            [NOT] = generate_type_3,
            [CLR] = generate_type_3,
            [INC] = generate_type_3,
            [DEC] = generate_type_3,
            [RED] = generate_type_3,
            [LEA] = generate_type_4,
            [JMP] = generate_type_5,
            [BNE] = generate_type_5,
            [JSR] = generate_type_5,
            [PRN] = generate_type_6,
            [RTS] = generate_type_7,
            [HLT] = generate_type_7
    };

    return generator_functions[opcode];
}
