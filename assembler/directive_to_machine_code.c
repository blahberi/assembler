//
// Author: Eitan H.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "directive_descriptor.h"
#include "words.h"
#include "../utils/utils.h"
#include "../errors.h"
#include "../symbol_table/symbol.h"
#include "../symbol_table/global_symbol_table.h"

void generate_data_directive(const DirectiveDescriptor* directiveDescriptor, const char* operands, AssemblerContext* context, Word* words){
    if (operands == NULL) {
        fprintf(stderr, "error");
        exit(EXIT_FAILURE); // TODO: Handle error properly
    }
    char** tokens = split_string_by_comma(operands);
    int i = context->DC;

    for (char** token = tokens; *token != NULL; token++) {
        trim_whitespace(*token);
        if (!is_number_signed(*token)) {
            fprintf(stderr, ERR_INVALID_CONSTANT, *token);
            exit(EXIT_FAILURE); // TODO: Handle error properly
        }
        int value = atoi(*token);
        if (value < MIN_LARGE_SIGNED_VALUE || value > MAX_LARGE_SIGNED_VALUE) {
        fprintf(stderr, ERR_CONSTANT_TOO_BIG);
            exit(EXIT_FAILURE); // TODO: Handle error properly
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
}

void generate_string_directive(const DirectiveDescriptor* directiveDescriptor, const char* operand, AssemblerContext* context, Word* words){
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
}

void generate_entry_directive(const DirectiveDescriptor* directiveDescriptor, const char* operand, AssemblerContext* context, Word* words){
    if (context->is_first_pass){
        return;
    }
    find_label_and_error(operand);
    Symbol *symbol = symbol_table_find(operand);

    symbol->is_entry = true;
}

void generate_extern_directive(const DirectiveDescriptor* directiveDescriptor, const char* operand, AssemblerContext* context, Word* words){
    if (!context->is_first_pass){
        return;
    }
    check_label_and_error(operand);
    Symbol *symbol = construct_symbol(operand, EXTERN_LABEL, 0, false);
    symbol_table_insert(symbol);
}