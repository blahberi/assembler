/*
 Author: Eitan H.
*/


#include <stdio.h>
#include <string.h>
#include "../symbol_table/global_symbol_table.h"
#include "../context/context.h"
#include "../../errors.h"
#include "assembly_strings.h"


int check_label_err_first_pass(const char* line, const char* label) { /* Check if label is valid in the first pass */
    if (symbol_table_is_in(label)) { /* Check if label already exists in the symbol table */
        fprintf(stderr, ERR_LABEL_ALREADY_EXISTS, label, line);
        goto error;
    }

    if (check_label(label)){ /* Check if label is valid */
        return 0;
    }

    if (check_register(label) || is_operation(label)) {  /* Check if label is a reserved keyword */
        fprintf(stderr, ERR_RESERVED_LABEL, label, line);
        goto error;
    }

    /* Check if label exceeds length limit */
    if (strlen(label) > MAX_LABEL_LENGTH) {
        fprintf(stderr, ERR_LABEL_TOO_LONG, label, line);
        goto error;
    }

    fprintf(stderr, ERR_INVALID_LABEL, label, line);
    goto error;

    error:
    return -1;
}

int check_label_err_second_pass(const char* line, const char* label) { /* Check if label is valid in the second pass */
    if (!symbol_table_is_in(label)) { /* Check if label is defined */
        fprintf(stderr, ERR_LABEL_NOT_DEFINED, label, line);
        return -1;
    }
    return 0;
}

int check_label_err(const char* label, const Context *context) { /* Check if label is valid and error accordingly */
    const char* line = context->line_descriptor->line;
    bool is_first_pass = context->assembler_context->is_first_pass;
    if (is_first_pass) {
        return check_label_err_first_pass(line, label);
    } else {
        return check_label_err_second_pass(line, label);
    }
}
