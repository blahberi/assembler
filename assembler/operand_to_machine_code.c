//
// Author: Eitan H. .
//

#include "operand_to_machine_code.h"
#include "../symbol_table/global_symbol_table.h"
#include "../utils/utils.h"
#include "are.h"
#include "operand_words.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int generate_immediate_operand(OperandDescriptor* descriptor, InstructionWord *instruction_word) {
    // bits 0-1: ARE
    // bits 2-13: Value

    int value = atoi(descriptor->operand + 1);
    ValueWord *word = (ValueWord *)instruction_word;
    word->ARE = ABSOLUTE;
    word->VALUE = value; // Value
    return 1;
}

int generate_direct_operand(OperandDescriptor* descriptor, InstructionWord *instruction_word) {
    // bits 0-1: ARE
    // bits 2-13: Address

    Symbol *symbol = symbol_table_find(descriptor->operand);
    ARE are = symbol->is_external ? EXTERNAL : RELOCATABLE;
    ValueWord *word = (ValueWord *)instruction_word;
    word->ARE = are;
    word->VALUE = symbol->value; // Address
    return 1;
}

int generate_index_operand(OperandDescriptor* descriptor, InstructionWord *instruction_word) {
    // First word bits 0-1: ARE
    // First word bits 2-13: Address

    // Second word bits 0-1: ARE
    // Second word bits 2-13: Index

    const char *operand = descriptor->operand;
    char *operand_copy = strdup(operand);
    char *address = strtok(operand_copy, "[");
    char *index_str = strtok(NULL, "]");

    int index;
    if (symbol_table_is_in(index_str)){
        index = symbol_table_find(index_str)->value;
    }
    else if (is_number_unsigned(index_str)){
        index = atoi(index_str);
    }
    else {
        fprintf(stderr, "Invalid index: %s\n", index_str);
        exit(EXIT_FAILURE); // TODO: Handle error appropriately
    }

    Symbol *symbol = symbol_table_find(address);
    ARE are = symbol->is_external ? EXTERNAL : RELOCATABLE;
    IndexMachineCode* mc = (IndexMachineCode*)instruction_word;
    mc->address_word.ARE = are;
    mc->address_word.VALUE = symbol->value; // Address
    mc->index_word.ARE = ABSOLUTE;
    mc->index_word.VALUE = index; // Index

    free(operand_copy);
    return 2;
}

int generate_register_operand(OperandDescriptor* descriptor, InstructionWord *instruction_word) {
    // bits 0-1: ARE
    // bits 2-4: Source register

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