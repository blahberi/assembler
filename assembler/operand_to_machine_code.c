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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int generate_immediate_operand(OperandDescriptor* descriptor, const AssemblerContext *context, Word *instruction_word) {
    // bits 0-1: ARE
    // bits 2-13: Value
    if (context->is_first_pass) {
        return 1;
    }

    char* str_value = descriptor->operand + 1; // Skip the '#' character
    int value;
    if (symbol_table_is_in(str_value)) {
        Symbol *symbol = symbol_table_find(str_value);
        if (symbol->type != MDEFINE) {
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
    ValueWord *word = (ValueWord *)instruction_word;
    word->ARE = ABSOLUTE;
    word->VALUE = value; // Value
    return 1;
}

int generate_direct_operand(OperandDescriptor* descriptor, const AssemblerContext *context, Word *instruction_word) {
    // bits 0-1: ARE
    // bits 2-13: Address

    if (context->is_first_pass) {
        return 1;
    }

    Symbol *symbol = symbol_table_find(descriptor->operand);
    ARE are = symbol->is_external ? EXTERNAL : RELOCATABLE;
    ValueWord *word = (ValueWord *)instruction_word;
    word->ARE = are;
    word->VALUE = symbol->value; // Address
    return 1;
}

int generate_index_operand(OperandDescriptor* descriptor, const AssemblerContext *context, Word *instruction_word) {
    // First word bits 0-1: ARE
    // First word bits 2-13: Address

    // Second word bits 0-1: ARE
    // Second word bits 2-13: Index

    if (context->is_first_pass) {
        return 2;
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
        if (symbol->type != MDEFINE) {
            fprintf(stderr, ERR_LABEL_MUST_BE_MDEFINE, index_str);
            exit(EXIT_FAILURE); // TODO: Handle error appropriately
        }
        index = symbol->value;
    }

    Symbol *symbol = symbol_table_find(address);
    ARE are = symbol->is_external ? EXTERNAL : RELOCATABLE;
    IndexMachineCode* mc = (IndexMachineCode*)instruction_word;
    mc->address_word.ARE = are;
    mc->address_word.VALUE = symbol->value; // Address
    mc->index_word.ARE = ABSOLUTE;
    mc->index_word.VALUE = index; // Index

    free(address);
    free(index_str);
    return 2;
}

int generate_register_operand(OperandDescriptor* descriptor, const AssemblerContext *context, Word *instruction_word) {
    // bits 0-1: ARE
    // bits 2-4: Source register

    if (context->is_first_pass) {
        return 1;
    }

    int reg_num = atoi(descriptor->operand + 1);
    RegisterWord *word = (RegisterWord*)instruction_word;
    word->ARE = ABSOLUTE;
    if (descriptor->is_dest) {
        word->DEST = reg_num; // Register number for destination operand
    } else {
        word->SRC = reg_num; // Register number for source operand
    }
    return 1;
}