//
// Author: Eitan H.
//



#include <stdio.h>
#include <string.h>
#include "context/context.h"
#include "utils/errors.h"
#include "utils/utils.h"
#include "utils/error_checking.h"
#include "symbol_table/symbol.h"
#include "symbol_table/global_symbol_table.h"

int generate_data_directive(Context *context){
    const char* line = context->line_descriptor->line;
    const char* operands = context->line_descriptor->operands;
    bool is_first_pass = context->assembler_context->is_first_pass;
    Word* words = context->data_words;

    int DC = context->assembler_context->DC;
    if (operands == NULL) {
        fprintf(stderr, ERR_DATA_EXPECTS_OPERANDS, line);
        return -1;
    }

    char** tokens = split_string_by_comma(operands);
    if (is_first_pass) {
        int length = comma_seperated_list_length(operands);
        DC += length;
        context->assembler_context->DC = DC;
        return 0;
    }

    for (char** token = tokens; *token != NULL; token++) {
        trim_whitespace(*token);
        int value;
        if (get_value_signed(*token, &value) != 0) {
            fprintf(stderr, ERR_INVALID_DATA_OPERAND, line);
            return -1;
        }
        (words+DC)->word = value;
        DC++;
    }
    // Free the tokens
    for (char** token = tokens; *token != NULL; token++) {
        free(*token);
    }
    free(tokens);

    context->assembler_context->DC = DC;
    return 0;
}

int generate_string_directive(Context *context){
    const char* line = context->line_descriptor->line;
    const char* operand = context->line_descriptor->operands;
    int DC = context->assembler_context->DC;
    Word* words = context->data_words;
    // Remove the quotes from the operand
    char* str = strdup(operand + 1);
    str[strlen(str) - 1] = '\0';

    for (; str[DC] != '\0'; DC++) {
        words[DC].word = (unsigned int)str[DC];
    }

    // Add null terminator
    words[DC].word = 0;
    DC++;

    free(str);
    context->assembler_context->DC = DC;
    return 0;
}

int generate_entry_directive(Context *context){
    const char* operand = context->line_descriptor->operands;
    bool is_first_pass = context->assembler_context->is_first_pass;

    if (is_first_pass){
        return 0;
    }
    if (check_label_err(operand, context) != 0){
        return -1;
    }
    Symbol *symbol = symbol_table_find(operand);

    symbol->is_entry = true;
    return 0;
}

int generate_extern_directive(Context *context){
    const char* operand = context->line_descriptor->operands;
    bool is_first_pass = context->assembler_context->is_first_pass;
    if (!is_first_pass){
        return 0;
    }
    if (check_label_err(operand, context) != 0) {
        return -1;
    }
    Symbol *symbol = construct_symbol(operand, EXTERN_LABEL, 0, false);
    symbol_table_insert(symbol);
    return 0;
}