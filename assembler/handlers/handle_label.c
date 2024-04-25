/*
 Author: Eitan H.
*/


#include <stdio.h>
#include "../context/context.h"
#include "../utils/error_checking.h"
#include "../symbol_table/symbol.h"
#include "../symbol_table/global_symbol_table.h"
#include "../../errors.h"

int handle_label_helper(Context *context, LABEL_TYPE type, int value) { /* A generic label handler which is used by the specific label handlers */
    const char* label = context->line_descriptor->label;
    bool is_first_pass = context->assembler_context->is_first_pass;
    Symbol *symbol;

    if (!is_first_pass){ /* If this is the second pass, we don't need to handle the label */
        return 0;
    }
    if (check_label_err(label, context) != 0) { /* Check if the label is valid and error if necessary */
        goto error;
    }
    symbol = construct_symbol(label, type, value, false); /* Construct a symbol for the label */
    symbol_table_insert(symbol); /* Insert the symbol into the symbol table */
    return 0;

    error:
    return -1;
}

int handle_label_instruction(Context *context) { /* For instructions */
    int IC = context->assembler_context->IC;
    return handle_label_helper(context, CODE_LABEL, IC);
}

int handle_label_data(Context *context){ /* For .data and .string directives */
    int DC = context->assembler_context->DC;
    return handle_label_helper(context, DATA_LABEL, DC);
}

int handle_label_extern(Context *context) { /* For .extern directive */
    const char* line = context->line_descriptor->line;
    printf(WARN_EXTERN_LABEL_IGNORED, line); /* Warn that the label is ignored */
    return 0;
}

int handle_label_entry(Context *context) { /* For .entry directive */
    const char* line = context->line_descriptor->line;
    printf(WARN_ENTRY_LABEL_IGNORED, line); /* Warn that the label is ignored */
    return 0;
}
