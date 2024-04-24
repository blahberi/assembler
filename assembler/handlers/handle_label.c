//
// Author: Eitan H.
//


#include <stdio.h>
#include "../context/context.h"
#include "../utils/error_checking.h"
#include "../symbol_table/symbol.h"
#include "../symbol_table/global_symbol_table.h"
#include "../utils/errors.h"

int handle_label_instruction(Context *context) { // For instructions
    const char* label = context->line_descriptor->label;
    bool is_first_pass = context->assembler_context->is_first_pass;
    int *IC = &context->assembler_context->IC;

    if (!is_first_pass){
        goto error;
    }
    if (check_label_err(label, context) != 0) {
        goto error;
    }
    Symbol *symbol = construct_symbol(label, CODE_LABEL, *IC, false);
    symbol_table_insert(symbol);
    return 0;

    error:
    return -1;
}

int handle_label_data(Context *context){ // For .data and .string directives
    const char* label = context->line_descriptor->label;
    bool is_first_pass = context->assembler_context->is_first_pass;
    int *DC = &context->assembler_context->IC;
    if (!is_first_pass){
        goto error;
    }
    if (check_label_err(label, context) != 0) {
        goto error;
    }
    Symbol *symbol = construct_symbol(label, DATA_LABEL, *DC, false);
    symbol_table_insert(symbol);
    return 0;

    error:
    return -1;
}

int handle_label_extern(Context *context) { // For .extern directive
    const char* line = context->line_descriptor->line;
    printf(WARN_EXTERN_LABEL_IGNORED, line);
    return 0;
}

int handle_label_entry(Context *context) { // For .entry directive
    const char* line = context->line_descriptor->line;
    printf(WARN_ENTRY_LABEL_IGNORED, line);
    return 0;
}