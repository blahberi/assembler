/*
 Author: Eitan H.
*/


#include <stdio.h>
#include <string.h>
#include "../symbol_table/global_symbol_table.h"
#include "../context/context.h"
#include "../../errors.h"
#include "assembly_strings.h"


int check_label_err_first_pass(const char* line, const char* label) {
    if (symbol_table_is_in(label)) {
        fprintf(stderr, ERR_LABEL_ALREADY_EXISTS, label, line);
        goto error;
    }

    if (check_label(label)){
        return 0;
    }

    /* Check if label is reserved for register */
    if (check_register(label) || is_operation(label)) {
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

int check_label_err_second_pass(const char* line, const char* label) {
    if (!symbol_table_is_in(label)) {
        fprintf(stderr, ERR_LABEL_NOT_DEFINED, label, line);
        return -1;
    }
    return 0;
}

int check_label_err(const char* label, const Context *context) {
    const char* line = context->line_descriptor->line;
    bool is_first_pass = context->assembler_context->is_first_pass;
    if (is_first_pass) {
        return check_label_err_first_pass(line, label);
    } else {
        return check_label_err_second_pass(line, label);
    }
}
