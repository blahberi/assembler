//
// Author: Eitan H.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "descriptors/directive_descriptor.h"
#include "words.h"
#include "utils/utils.h"
#include "symbol_table/global_symbol_table.h"
#include "utils/error_checking.h"
#include "utils/errors.h"

int generate_data_directive(const DirectiveDescriptor* directiveDescriptor, const char* operands, const char* line, AssemblerContext* context, Word* words){
    if (operands == NULL) {
        fprintf(stderr, ERR_DATA_EXPECTS_OPERANDS, line);
        return -1;
    }

    char** tokens = split_string_by_comma(operands);
    if (context->is_first_pass) {
        int length = comma_seperated_list_length(operands);
        context->DC += length;
        return 0;
    }

    int i = context->DC;
    for (char** token = tokens; *token != NULL; token++) {
        trim_whitespace(*token);
        int value;
        if (get_value_signed(*token, &value) != 0) {
            fprintf(stderr, ERR_INVALID_DATA_OPERAND, line);
            return -1;
        }
        (words+i)->word = value;
        i++;
    }
    // Free the tokens
    for (char** token = tokens; *token != NULL; token++) {
        free(*token);
    }
    free(tokens);

    context->DC = i; // Increment the data counter by the number of words generated
    return 0;
}

int generate_string_directive(const DirectiveDescriptor* directiveDescriptor, const char* operand, const char* line, AssemblerContext* context, Word* words){
    // Remove the quotes from the operand
    char* str = strdup(operand + 1);
    str[strlen(str) - 1] = '\0';

    int i;
    for (i = context->DC; str[i] != '\0'; i++) {
        words[i].word = (int)str[i];
    }

    // Add null terminator
    words[i].word = 0;
    i++;

    free(str);
    context->DC = i; // Increment the data counter by the number of words generated
    return 0;
}

int generate_entry_directive(const DirectiveDescriptor* directiveDescriptor, const char* operand, const char* line, AssemblerContext* context, Word* words){
    if (context->is_first_pass){
        return 0;
    }
    if (check_label_err(line, operand, context) != 0){
        return -1;
    }
    Symbol *symbol = symbol_table_find(operand);

    symbol->is_entry = true;
    return 0;
}

int generate_extern_directive(const DirectiveDescriptor* directiveDescriptor, const char* operand, const char* line, AssemblerContext* context, Word* words){
    if (!context->is_first_pass){
        return 0;
    }
    if (check_label_err(line, operand, context) != 0) {
        return -1;
    }
    Symbol *symbol = construct_symbol(operand, EXTERN_LABEL, 0, false);
    symbol_table_insert(symbol);
    return 0;
}