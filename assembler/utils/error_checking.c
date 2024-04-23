//
// Author: Eitan H.
//


#include <stdio.h>
#include <tchar.h>
#include "assembly_strings.h"
#include "../assembler_context.h"
#include "../symbol_table/global_symbol_table.h"
#include "errors.h"



int check_label_err_first_pass(const char* line, const char* label) {
    if (symbol_table_is_in(label)) {
        fprintf(stderr, ERR_LABEL_ALREADY_EXISTS, label, line);
        return -1;
    }

    if (check_label(label)){
        return 0;
    }

    // Check if label is reserved for register
    if (check_register(label) || is_instruction(label)) {
        fprintf(stderr, ERR_RESERVED_LABEL, label, line);
        return -1;
    }

    // Check if label exceeds length limit
    if (strlen(label) > MAX_LABEL_LENGTH) {
        fprintf(stderr, ERR_LABEL_TOO_LONG, label, line);
        return -1;
    }

    fprintf(stderr, ERR_INVALID_LABEL, label, line);
}

int check_label_err_second_pass(const char* line, const char* label) {
    if (!symbol_table_is_in(label)) {
        fprintf(stderr, ERR_LABEL_NOT_DEFINED, label, line);
        return -1;
    }
    return 0;
}

int check_label_err(const char* line, const char* label, const AssemblerContext* context) {
    if (context->is_first_pass) {
        return check_label_err_first_pass(line, label);
    } else {
        return check_label_err_second_pass(line, label);
    }
}
