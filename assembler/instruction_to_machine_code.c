/*
 Author: Eitan H.
*/


#include <stdio.h>
#include "context/context.h"
#include "../errors.h"

int generate_first_word(Context *context) { /* Generate the machine code for the first word of the instruction */
    /*
     * bits 0-1: ARE
     * bits 2-3: Destination addressing mode
     * bits 4-5: Source addressing mode
     * bits 6-9: Opcode
     * bits 10-13: padding
     */
    bool is_first_pass = context->assembler_context->is_first_pass;
    Word *instruction_word = context->instruction_words;
    OperationDescriptor *descriptor;
    OperandDescriptor *operands;
    ADDR_MODE dest;
    ADDR_MODE src;
    int *IC = &context->assembler_context->IC;
    int operand_count;
    FirstWord *word;

    if (!is_first_pass) {
        (*IC)++;

        return 0;
    }

    descriptor = context->instruction->operation;
    operands = context->instruction->operands;

    dest = 0;
    src = 0;
    operand_count = context->instruction->operand_count;
    if (operand_count == 1) {
        dest = operands[0].addr_mode;
    } else if (operand_count == 2) {
        dest = operands[1].addr_mode;
        src = operands[0].addr_mode;
    }

    word = (FirstWord*)(instruction_word+(*IC));
    word->ARE = ABSOLUTE;
    word->DEST = dest;
    word->SRC = src;
    word->OPCODE = descriptor->opcode;
    (*IC)++;
    return 0;
}

int generate_two_word_instruction(Context *context) { /* Generate machine code for instructions that take two words */
    OperandDescriptor *operands = context->instruction->operands;
    OperandDescriptor *src = operands; /* Source operand */
    OperandDescriptor *dest = operands+1; /* Destination operand */
    int *IC = &context->assembler_context->IC;
    int res1;
    int res2;

    src->is_dest = false; /* Source operand is not the destination */
    dest->is_dest = true; /* Destination operand is the destination */
    generate_first_word(context); /* Generate the machine code for the first word */
    res1 = src->generate(src, context);
    if (src->addr_mode == REGISTER && dest->addr_mode == REGISTER) { /* If both operands are registers */
        (*IC)--; /* Decrement the instruction counter since the machine code they generate overlap */
    }
    res2 = dest->generate(dest, context); /* Generate the destination operand */

    if (res1 != 0 || res2 != 0) { /* Check if there was an error */
        goto error;
    }
    return 0;

    error:
    return -1;
}

int generate_one_word_instruction(Context *context) { /* Generate machine code for instructions that take one word */
    OperandDescriptor *operands = context->instruction->operands;
    OperandDescriptor *dest = operands; /* Destination operand */
    int res1;
    int res2;

    dest->is_dest = true; /* Set destination flag to be true */
    res1 = generate_first_word(context); /* Generate the machine code for the first word */
    res2 = dest->generate(dest, context);  /* Generate the machine code for the operand */
    if (res1 != 0 || res2 != 0) { /* Check if there was an error */
        goto error;
    }
    return 0;

    error:
    return -1;
}

int generate_zero_word_instruction(Context *context) { /* Generate machine code for instructions that take zero words */
    return generate_first_word(context); /* Just generate the machine code for the first word */
}

int generate_type_1(Context *context) { /* mov, add, sub */
    /*
     * src operand: Immediate, Direct, Index, Register
     * dest operand: Direct, Index, Register
     */

    bool is_first_pass = context->assembler_context->is_first_pass;
    const char *line = context->line_descriptor->line;
    int operand_count = context->instruction->operand_count;
    OperandDescriptor dest;

    if (operand_count != 2) {
        if (is_first_pass){
            fprintf(stderr, ERR_EXPECTED_TWO_OPERANDS, line);
        }
        goto error;
    }

    dest = context->instruction->operands[1];

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

int generate_type_2(Context *context) {  /* cmp */
    /*
     * src operand: Immediate, Direct, Index, Register
     * dest operand: Immediate, Direct, Index, Register
     */

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

int generate_type_3(Context *context) { /* not, clr, inc, dec, red */
    /*
     * src operand: None
     * dest operand: Direct, Index, Register
     */

    bool is_first_pass = context->assembler_context->is_first_pass;
    const char *line = context->line_descriptor->line;
    int operand_count = context->instruction->operand_count;
    OperandDescriptor dest;

    if (operand_count != 1) {
        if (is_first_pass) {
            fprintf(stderr, ERR_EXPECTED_ONE_OPERAND, line);
        }
        goto error;
    }

    dest = context->instruction->operands[0];

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

int generate_type_4(Context *context) { /* lea */
    /*
     * src operand: Direct, Index
     * dest operand: Direct, Index, Register
     */

    bool is_first_pass = context->assembler_context->is_first_pass;
    const char *line = context->line_descriptor->line;
    int operand_count = context->instruction->operand_count;
    OperandDescriptor src;
    OperandDescriptor dest;

    if (operand_count != 2) {
        if (is_first_pass) {
            fprintf(stderr, ERR_EXPECTED_TWO_OPERANDS, line);
        }
        goto error;
    }

    src = context->instruction->operands[0];
    dest = context->instruction->operands[1];

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

int generate_type_5(Context *context) { /* jmp, bne, jsr */
    /*
     * src operand: None
     * dest operand: Direct, Register
     */
    bool is_first_pass = context->assembler_context->is_first_pass;
    const char *line = context->line_descriptor->line;
    int operand_count = context->instruction->operand_count;
    OperandDescriptor dest;

    if (operand_count != 1) {
        if (is_first_pass) {
            fprintf(stderr, ERR_EXPECTED_ONE_OPERAND, line);
        }
        goto error;
    }

    dest = context->instruction->operands[0];

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

int generate_type_6(Context *context) { /* prn */
    /*
     * src operand: None
     * dest operand: Immediate, Direct, Index, Register
     */

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

int generate_type_7(Context *context) { /* rts, hlt */
    /*
     * src operand: None
     * dest operand: None
     */

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

int (*get_instruction_generator(OPCODE opcode))(Context*){ /* Get the generator function given the opcode */
    int (*generator_functions[])(Context*) = {
            generate_type_1, /* mov */
            generate_type_2, /* cmp */
            generate_type_1, /* add */
            generate_type_1, /* sub */
            generate_type_3, /* not */
            generate_type_3, /* clr */
            generate_type_4, /* lea */
            generate_type_3, /* inc */
            generate_type_3, /* dec */
            generate_type_5, /* jmp */
            generate_type_5, /* bne */
            generate_type_3, /* red */
            generate_type_6, /* prn */
            generate_type_5, /* jsr */
            generate_type_7, /* rts */
            generate_type_7, /* hlt */
    };

    return generator_functions[opcode];
}
