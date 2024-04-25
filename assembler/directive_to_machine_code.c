//
// Author: Eitan H.
//



#include <stdio.h>
#include <malloc.h>
#include "context/context.h"
#include "../errors.h"
#include "utils/utils.h"
#include "utils/error_checking.h"
#include "symbol_table/symbol.h"
#include "symbol_table/global_symbol_table.h"
#include "utils/assembly_strings.h"

int generate_data_directive(Context *context){
    const char* line = context->line_descriptor->line;
    const char* operands = context->line_descriptor->operands;
    bool is_first_pass = context->assembler_context->is_first_pass;
    Word* words = context->data_words;

    int *DC = &context->assembler_context->DC;
    if (operands == NULL) {
        fprintf(stderr, ERR_DATA_EXPECTS_OPERANDS, line);
        goto error;
    }

    char** tokens = split_string_by_comma(operands);
    if (is_first_pass) {
        int length = comma_seperated_list_length(operands);
        *DC += length;
        return 0;
    }

    for (char** token = tokens; *token != NULL; token++) {
        trim_whitespace(*token);
        int value;
        if (get_value_signed(*token, &value) != 0) {
            fprintf(stderr, ERR_INVALID_DATA_OPERAND, line);
            goto error;
        }
        (words+(*DC))->word = value;
        (*DC)++;
    }
    return 0;

    error:
    return -1;
}

int generate_string_directive(Context *context){
    const char* line = context->line_descriptor->line;
    const char* operand = context->line_descriptor->operands;
    int *DC = &context->assembler_context->DC;
    Word* words = context->data_words;
    char* str = get_string_from_quotes(operand);
    if (str == NULL) {
        fprintf(stderr, ERR_INVALID_STRING, line);
        goto error;
    }

    for (; str[*DC] != '\0'; (*DC)++) {
        words[*DC].word = (unsigned int)str[*DC];
    }

    // Add null terminator
    (*DC)++;
    words[*DC].word = 0;
    return 0;

    error:
    return -1;
}

int generate_entry_directive(Context *context){
    const char* line = context->line_descriptor->line;
    const char* operand = context->line_descriptor->operands;
    bool is_first_pass = context->assembler_context->is_first_pass;

    if (is_first_pass){
        return 0;
    }
    if (check_label_err(operand, context) != 0){
        goto error;
    }
    Symbol *symbol = symbol_table_find(operand);
    if (symbol->type == EXTERN_LABEL){
        fprintf(stderr, ERR_CANNOT_ENTRY_EXTERN_LABEL, operand, line);
        goto error;
    }
    symbol->is_entry = true;
    return 0;

    error:
    return -1;
}

int generate_extern_directive(Context *context){
    const char* operand = context->line_descriptor->operands;
    bool is_first_pass = context->assembler_context->is_first_pass;
    if (!is_first_pass){
        return 0;
    }
    if (check_label_err(operand, context) != 0) {
        goto error;
    }
    Symbol *symbol = construct_symbol(operand, EXTERN_LABEL, 0, false);
    symbol_table_insert(symbol);
    return 0;

    error:
    return -1;
}