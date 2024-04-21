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

int generate_data_directive(const DirectiveDescriptor* directiveDescriptor, const char* operands, AssemblerContext* context, Word* words){
    char** tokens = split_string_by_comma(operands);
    int i = 0;

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
        words[i].word = value;
        i++;
    }
    // Free the tokens
    for (char** token = tokens; *token != NULL; token++) {
        free(*token);
    }
    free(tokens);

    context->DC += i; // Increment the data counter by the number of words generated

    return i; // Return the number of words generated
}

int generate_string_directive(const DirectiveDescriptor* directiveDescriptor, const char* operand, AssemblerContext* context, Word* words){
    // Remove the quotes from the operand
    char* str = strdup(operand + 1);
    str[strlen(str) - 1] = '\0';

    int i;
    for (i = 0; str[i] != '\0'; i++) {
        words[i].word = (int)str[i];
    }

    // Add null terminator
    words[i].word = 0;

    free(str);
    i++;
    context->DC += i; // Increment the data counter by the number of words generated
    return i; // Return the number of words generated
}