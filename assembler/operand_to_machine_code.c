//
// Author: Eitan H.
//

#include "operand_to_machine_code.h"
#include "../symbol_table/global_symbol_table.h"
#include "../utils/utils.h"
#include "are.h"
#include "words.h"
#include "assembly_strings.h"
#include "handle_label.h"
#include "../errors.h"
#include "../extern_handler/extern_handler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void generate_immediate_operand(OperandDescriptor* descriptor, AssemblerContext *context, Word *instruction_word) {
    // bits 0-1: ARE
    // bits 2-13: Value
    if (context->is_first_pass) {
        context->IC += 1;
        return;
    }

    const char* str_value = descriptor->operand + 1; // Skip the '#' character
    int value;
    if (symbol_table_is_in(str_value)) {
        find_label_and_error(str_value); // Check if label exists
        Symbol *symbol = symbol_table_find(str_value);
        if (symbol->type != MDEFINE_LABEL) {
            fprintf(stderr, ERR_LABEL_MUST_BE_MDEFINE, str_value);
            exit(EXIT_FAILURE); // TODO: Handle error appropriately
        }
        value = symbol->value;
    }
    else if (is_number_signed(str_value)) {
        value = atoi(str_value);
        if (value < MIN_SIGNED_VALUE || value > MAX_SIGNED_VALUE) {
            fprintf(stderr, ERR_CONSTANT_TOO_BIG);
            exit(EXIT_FAILURE); // TODO: Handle error appropriately
        }
    }
    else {
        fprintf(stderr, ERR_INVALID_IMMEDIATE_VALUE, str_value);
        exit(EXIT_FAILURE); // TODO: Handle error appropriately
    }
    int ic = context->IC;
    ValueWord *word = (ValueWord *)(instruction_word+ic);
    word->ARE = ABSOLUTE;
    word->VALUE = value; // Value

    context->IC += 1;
}

void generate_direct_operand(OperandDescriptor* descriptor, AssemblerContext *context, Word *instruction_word) {
    // bits 0-1: ARE
    // bits 2-13: Address

    if (context->is_first_pass) {
        context->IC += 1;
        return;
    }

    int ic = context->IC;
    find_label_and_error(descriptor->operand);
    Symbol *symbol = symbol_table_find(descriptor->operand);
    if (symbol->type == EXTERN_LABEL){
        add_extern_label_usage(symbol->name, ic);
    }

    ARE are = symbol->type==EXTERN_LABEL ? EXTERNAL : RELOCATABLE;
    ValueWord *word = (ValueWord *)(instruction_word+ic);
    word->ARE = are;
    word->VALUE = symbol->value; // Address

    context->IC += 1;
}

void generate_index_operand(OperandDescriptor* descriptor, AssemblerContext *context, Word *instruction_word) {
    // First word bits 0-1: ARE
    // First word bits 2-13: Address

    // Second word bits 0-1: ARE
    // Second word bits 2-13: Index

    if (context->is_first_pass) {
        context->IC += 2;
        return;
    }

    char* address = malloc(strlen(descriptor->operand) + 1);
    char* index_str = malloc(strlen(descriptor->operand) + 1);
    parse_index_operand(descriptor->operand, address, index_str);

    int index;
    find_label_and_error(address);
    if (is_number_unsigned(index_str)) {
        index = atoi(index_str);
        if (index > MAX_UNSIGNED_VALUE) {
            fprintf(stderr, ERR_CONSTANT_TOO_BIG);
            exit(EXIT_FAILURE); // TODO: Handle error appropriately

        }
    }
    else {
        find_label_and_error(index_str);
        Symbol *symbol = symbol_table_find(index_str);
        if (symbol->type != MDEFINE_LABEL) {
            fprintf(stderr, ERR_LABEL_MUST_BE_MDEFINE, index_str);
            exit(EXIT_FAILURE); // TODO: Handle error appropriately
        }
        index = symbol->value;
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
}

void generate_register_operand(OperandDescriptor* descriptor, AssemblerContext *context, Word *instruction_word) {
    // bits 0-1: ARE
    // bits 2-4: Source register

    if (context->is_first_pass) {
        context->IC += 1;
        return;
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
}