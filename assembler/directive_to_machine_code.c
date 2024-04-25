/*
 Author: Eitan H.
*/

#include <stdio.h>
#include "context/context.h"
#include "../errors.h"
#include "utils/error_checking.h"
#include "symbol_table/symbol.h"
#include "symbol_table/global_symbol_table.h"
#include "utils/assembly_strings.h"

int generate_data_directive(Context *context){ /* Generate machine code for .data directive */
    const char* line = context->line_descriptor->line;
    const char* operands = context->line_descriptor->operands;
    char ** tokens;
    char** token;
    int value;
    int length;
    bool is_first_pass = context->assembler_context->is_first_pass;
    Word* words = context->data_words;
    int *DC = &context->assembler_context->DC;

    if (operands == NULL) { /* Check if there are operands */
        if (is_first_pass){
            fprintf(stderr, ERR_DATA_EXPECTS_OPERANDS, line); /* If there are no operands, print an error */
        }
        goto error;
    }

    tokens = split_string_by_comma(operands); /* Split the operands by commas */
    if (is_first_pass) { /* If this is the first pass */
        length = comma_seperated_list_length(operands); /* Get the length of the comma seperated list */
        *DC += length; /* Increment the data counter by the length */
        return 0; /* Return, we don't need to generate machine code */
    }

    /* If this is the second pass */
    for (token = tokens; *token != NULL; token++) { /* Iterate over the tokens */
        trim_whitespace(*token); /* Remove whitespace from the token */
        if (get_value_signed(*token, &value) != 0) { /* Get the value of the token */
            fprintf(stderr, ERR_INVALID_DATA_OPERAND, line); /* If the value is invalid, print an error */
            goto error;
        }
        (words+(*DC))->word = value; /* Set the word in the data words */
        (*DC)++; /* Increment the data counter */
    }
    return 0;

    error:
    return -1;
}

int generate_string_directive(Context *context){ /* Generate machine code for .string directive */
    const char* line = context->line_descriptor->line;
    const char* operand = context->line_descriptor->operands;
    int *DC = &context->assembler_context->DC;
    Word* words = context->data_words;
    char* str = get_string_from_quotes(operand);
    bool is_first_pass = context->assembler_context->is_first_pass;

    if (str == NULL) { /* Check if the string is valid */
        if (is_first_pass){
            fprintf(stderr, ERR_INVALID_STRING, line);  /* If the string is invalid, print an error */
        }
        goto error;
    }

    for (; str[*DC] != '\0'; (*DC)++) { /* Iterate over the string */
        words[*DC].word = (unsigned int)str[*DC]; /* Set the word in the data words */
    }

    /* Add null terminator */
    (*DC)++;
    words[*DC].word = 0;
    return 0;

    error:
    return -1;
}

int generate_entry_directive(Context *context){ /* Mark symbol as entry. */
    const char* line = context->line_descriptor->line;
    const char* operand = context->line_descriptor->operands;
    bool is_first_pass = context->assembler_context->is_first_pass;
    Symbol* symbol;

    if (is_first_pass){
        return 0;
    }
    if (check_label_err(operand, context) != 0){
        goto error;
    }
    symbol = symbol_table_find(operand);
    if (symbol->type == EXTERN_LABEL){
        fprintf(stderr, ERR_CANNOT_ENTRY_EXTERN_LABEL, operand, line);
        goto error;
    }
    symbol->is_entry = true;
    return 0;

    error:
    return -1;
}

int generate_extern_directive(Context *context){ /* Add symbol to symbol table as external. */
    const char* operand = context->line_descriptor->operands;
    bool is_first_pass = context->assembler_context->is_first_pass;
    Symbol* symbol;

    if (!is_first_pass){
        return 0;
    }
    if (check_label_err(operand, context) != 0) {
        goto error;
    }
    symbol = construct_symbol(operand, EXTERN_LABEL, 0, false);
    symbol_table_insert(symbol);
    return 0;

    error:
    return -1;
}
