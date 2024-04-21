//
// Author: Eitan H.
//

#include <stdio.h>
#include <stdlib.h>
#include "assembler_context.h"
#include "assembly_strings.h"
#include "../errors.h"
#include "../symbol_table/symbol.h"
#include "../symbol_table/global_symbol_table.h"

void check_label_and_error(const char* label) {
    switch (check_label(label)) {
        case INVALID_LABEL:
            fprintf(stderr, ERR_INVALID_LABEL_NAME, label);
            exit(EXIT_FAILURE);
        case INVALID_LABEL_LENGTH:
            fprintf(stderr, ERR_LABEL_TOO_LONG, label);
            exit(EXIT_FAILURE);
        case VALID_LABEL:
            break;
    }
}

void find_label_and_error(const char* label) {
    Symbol *symbol = symbol_table_find(label);
    if (symbol == NULL) {
        fprintf(stderr, ERR_LABEL_NOT_FOUND, label);
        exit(EXIT_FAILURE);
    }
}

int handle_label_define(const char* label, const AssemblerContext* context) { // For .define directive
    if (!context->is_first_pass){
        return -1;
    }
    check_label_and_error(label);
    Symbol *symbol = construct_symbol(label, MDEFINE, context->IC, false, false);
    symbol_table_insert(symbol);
    return 0;
}

int handle_label_instruction(const char* label, const AssemblerContext* context) { // For instructions
    if (!context->is_first_pass){
        return -1;
    }
    check_label_and_error(label);
    Symbol *symbol = construct_symbol(label, CODE, context->IC, false, false);
    symbol_table_insert(symbol);
    return 0;
}

int handle_label_data(const char* label, const AssemblerContext* context){ // For .data and .string directives
    if (!context->is_first_pass){
        return -1;
    }
    check_label_and_error(label);
    Symbol *symbol = construct_symbol(label, DATA, context->DC, false, false);
    symbol_table_insert(symbol);
    return 0;
}

int handle_label_extern(const char* label, const AssemblerContext* context) { // For .extern directive
    if (!context->is_first_pass){
        return -1;
    }
    check_label_and_error(label);
    Symbol *symbol = construct_symbol(label, EXTERN, 0, false, false);
    symbol_table_insert(symbol);
    return 0;
}

int handle_label_entry(const char* label, const AssemblerContext *context) { // For .entry directive
    if (context->is_first_pass) {
        return -1;
    }

    find_label_and_error(label);
    Symbol *symbol = symbol_table_find(label);
    symbol->is_entry = true;
    return 0;
}