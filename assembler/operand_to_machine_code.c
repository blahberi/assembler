//
// Author: Eitan H.
//

#include "operand_to_machine_code.h"
#include "are.h"
#include "words.h"
#include "utils/assembly_strings.h"
#include "handlers/handle_label.h"
#include "symbol_table/global_symbol_table.h"
#include "utils/utils.h"
#include "utils/error_checking.h"
#include "extern_handler/extern_handler.h"
#include "utils/errors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int generate_immediate_operand(OperandDescriptor* descriptor, const char* line, AssemblerContext *context, Word *instruction_word) {
    // bits 0-1: ARE
    // bits 2-13: Value
    if (context->is_first_pass) {
        context->IC += 1;
        return 0;
    }

    const char* str_value = descriptor->operand + 1; // Skip the '#' character
    int value;
    if (get_value_signed(str_value, &value) != 0) {
        fprintf(stderr, ERR_IMMEDIATE_MUST_BE_NUMBER, line);
        return -1;
    }
    int ic = context->IC;
    ValueWord *word = (ValueWord *)(instruction_word+ic);
    word->ARE = ABSOLUTE;
    word->VALUE = value;

    context->IC += 1;
    return 0;
}

int generate_direct_operand(OperandDescriptor* descriptor, const char* line, AssemblerContext *context, Word *instruction_word) {
    // bits 0-1: ARE
    // bits 2-13: Address

    if (context->is_first_pass) {
        context->IC += 1;
        return 0;
    }

    int ic = context->IC;
    if (check_label_err(line, descriptor->operand, context) != 0) {
        return -1;
    }
    Symbol *symbol = symbol_table_find(descriptor->operand);
    if (symbol->type == EXTERN_LABEL){
        add_extern_label_usage(symbol->name, ic);
    }

    ARE are = symbol->type==EXTERN_LABEL ? EXTERNAL : RELOCATABLE;
    ValueWord *word = (ValueWord *)(instruction_word+ic);
    word->ARE = are;
    word->VALUE = symbol->value; // Address

    context->IC += 1;
    return 0;
}

int generate_index_operand(OperandDescriptor* descriptor, const char* line, AssemblerContext *context, Word *instruction_word) {
    // First word bits 0-1: ARE
    // First word bits 2-13: Address

    // Second word bits 0-1: ARE
    // Second word bits 2-13: Index

    if (context->is_first_pass) {
        context->IC += 2;
        return 0;
    }

    char* address = malloc(strlen(descriptor->operand) + 1);
    char* index_str = malloc(strlen(descriptor->operand) + 1);
    parse_index_operand(descriptor->operand, address, index_str);

    int index;
    if (check_label_err(line, address, context) != 0){
        return -1;
    }
    if (get_value_unsigned(index_str, &index) != 0) {
        fprintf(stderr, ERR_INDEX_MUST_BE_NUMBER, line);
        return -1;
    }

    int ic = context->IC;
    Symbol *symbol = symbol_table_find(address);
    if (symbol->type == EXTERN_LABEL){
        add_extern_label_usage(symbol->name, ic);
    }

    ARE are = symbol->type==EXTERN_LABEL ? EXTERNAL : RELOCATABLE;
    IndexMachineCode* mc = (IndexMachineCode*)(instruction_word+ic);
    mc->address_word.ARE = are;
    mc->address_word.VALUE = symbol->value; // Address
    mc->index_word.ARE = ABSOLUTE;
    mc->index_word.VALUE = index; // Index

    free(address);
    free(index_str);

    context->IC += 2;
    return 0;
}

int generate_register_operand(OperandDescriptor* descriptor, const char* line, AssemblerContext *context, Word *instruction_word) {
    // bits 0-1: ARE
    // bits 2-4: Source register

    if (context->is_first_pass) {
        context->IC += 1;
        return 0;
    }

    int ic = context->IC;
    int reg_num = atoi(descriptor->operand + 1);
    RegisterWord *word = (RegisterWord*)(instruction_word+ic);
    word->ARE = ABSOLUTE;
    if (descriptor->is_dest) {
        word->DEST = reg_num; // Register number for destination operand
    } else {
        word->SRC = reg_num; // Register number for source operand
    }

    context->IC += 1;
    return 0;
}