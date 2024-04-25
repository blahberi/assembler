/*
 Author: Eitan H.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "context/context.h"
#include "../errors.h"
#include "utils/error_checking.h"
#include "symbol_table/symbol.h"
#include "symbol_table/global_symbol_table.h"
#include "extern_handler/extern_handler.h"
#include "utils/assembly_strings.h"
#include "../memory_allocator/memory_allocator.h"

int generate_immediate_operand(OperandDescriptor* descriptor, Context *context) {
    /*
     * bits 0-1: ARE
     * bits 2-13: Value
     */

    const char* line = context->line_descriptor->line;
    Word *instruction_word = context->instruction_words;
    bool is_first_pass = context->assembler_context->is_first_pass;
    int *IC = &context->assembler_context->IC;
    const char* str_value;
    int value;
    ValueWord *word;

    if (is_first_pass) {
        (*IC)++;
        return 0;
    }

    str_value = descriptor->operand + 1; /* Skip the '#' character */
    if (get_value_signed(str_value, &value) != 0) {
        fprintf(stderr, ERR_IMMEDIATE_MUST_BE_NUMBER, line);
        goto error;
    }
    word = (ValueWord *)(instruction_word+(*IC));
    word->ARE = ABSOLUTE;
    word->VALUE = value;

    (*IC)++;
    return 0;

    error:
    return -1;
}

int generate_direct_operand(OperandDescriptor* descriptor, Context *context) {
    /*
     * bits 0-1: ARE
     * bits 2-13: Address
     */

    const char* line = context->line_descriptor->line;
    Word *instruction_word = context->instruction_words;
    bool is_first_pass = context->assembler_context->is_first_pass;
    int *IC = &context->assembler_context->IC;
    Symbol *symbol;
    ARE are;
    ValueWord *word;

    if (is_first_pass) {
        (*IC)++;
        return 0;
    }
    if (check_label_err(descriptor->operand, context) != 0) {
        goto error;
    }
    symbol = symbol_table_find(descriptor->operand);
    if (symbol->type == MDEFINE_LABEL) {
        fprintf(stderr, ERR_DIRECT_CANNOT_BE_MDEFINE, descriptor->operand, line);
        goto error;
    }
    if (symbol->type == EXTERN_LABEL) {
        add_extern_label_usage(symbol->name, *IC);
    }

    are = symbol->type==EXTERN_LABEL ? EXTERNAL : RELOCATABLE;
    word = (ValueWord *)(instruction_word+(*IC));
    word->ARE = are;
    word->VALUE = symbol->value; /* Address */

    (*IC)++;
    return 0;

    error:
    return -1;
}

int generate_index_operand(OperandDescriptor* descriptor, Context *context) {
    /*
     * First word bits 0-1: ARE
     * First word bits 2-13: Address
     *
     * Second word bits 0-1: ARE
     * Second word bits 2-13: Index
     */

    const char* line = context->line_descriptor->line;
    Word *instruction_word = context->instruction_words;
    bool is_first_pass = context->assembler_context->is_first_pass;
    int *IC = &context->assembler_context->IC;
    char* address;
    char* index_str;
    int index;
    ARE are;
    Symbol* symbol;
    IndexMachineCode* mc;

    if (is_first_pass) {
        *IC += 2;
        return 0;
    }

    address = malloc_track(strlen(descriptor->operand) + 1);
    index_str = malloc_track(strlen(descriptor->operand) + 1);
    parse_index_operand(descriptor->operand, address, index_str);

    if (check_label_err(address, context) != 0){
        goto error;
    }
    if (get_value_unsigned(index_str, &index) != 0) {
        fprintf(stderr, ERR_INDEX_MUST_BE_NUMBER, line);
        goto error;
    }

    symbol = symbol_table_find(address);
    if (symbol->type == EXTERN_LABEL){
        add_extern_label_usage(symbol->name, *IC);
    }
    if (symbol->type == MDEFINE_LABEL) {
        fprintf(stderr, ERR_BASE_LABEL_CANNOT_BE_MDEFINE, address, line);
        goto error;
    }

    are = symbol->type==EXTERN_LABEL ? EXTERNAL : RELOCATABLE;
    mc = (IndexMachineCode*)(instruction_word+(*IC));
    mc->address_word.ARE = are;
    mc->address_word.VALUE = symbol->value; /* Address */
    mc->index_word.ARE = ABSOLUTE;
    mc->index_word.VALUE = index; /* Index */

    *IC += 2;
    return 0;

    error:
    return -1;
}

int generate_register_operand(OperandDescriptor* descriptor, Context *context) {
    /*
     * bits 0-1: ARE
     * bits 2-4: Destination register number
     * bits 5-7: Source register number
     */

    Word *instruction_word = context->instruction_words;
    bool is_first_pass = context->assembler_context->is_first_pass;
    int *IC = &context->assembler_context->IC;
    int reg_num;
    RegisterWord *word;

    if (is_first_pass) {
        (*IC)++;
        return 0;
    }

    reg_num = atoi(descriptor->operand + 1);
    word = (RegisterWord*)(instruction_word+(*IC));
    word->ARE = ABSOLUTE;
    if (descriptor->is_dest) {
        word->DEST = reg_num; /* Register number for destination operand */
    } else {
        word->SRC = reg_num; /* Register number for source operand */
    }

    (*IC)++;
    return 0;
}
