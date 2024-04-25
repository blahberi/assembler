/*
 Author: Eitan H.
*/

#include <string.h>
#include <stdio.h>
#include "../context/assembler_context.h"
#include "../utils/assembly_strings.h"
#include "../descriptors/directive_descriptor.h"
#include "../symbol_table/global_symbol_table.h"
#include "../../errors.h"
#include "../utils/error_checking.h"
#include "../context/context.h"

int handle_define_line(Context *context) {
    const char* sentence;
    char* operands;
    char* label;
    char* value_str;
    int value;
    Symbol *symbol;

    if (!context->assembler_context->is_first_pass) {
        return 0;
    }
    if (context->line_descriptor->is_label) {
        fprintf(stderr, ERR_DEFINE_GOT_LABEL, context->line_descriptor->line);
        goto error;
    }
    sentence = context->line_descriptor->sentence;
    operands = get_operands(sentence);
    context->line_descriptor->operands = operands;
    label = strtok(operands, "=");
    trim_whitespace(label);

    value_str = strtok(NULL, "=");
    trim_whitespace(value_str);

    if (label == NULL || value_str == NULL) {
        fprintf(stderr, ERR_DEFINE_DIDNT_GET_VALUE, context->line_descriptor->line);
        goto error;
    }

    if (check_label_err(label, context) != 0) {
        goto error;
    }

    if (get_value_signed(value_str, &value) != 0) {
        fprintf(stderr, ERR_INVALID_DEFINE_VALUE, context->line_descriptor->line);
        goto error;
    }

    symbol = construct_symbol(label, MDEFINE_LABEL, value, false);
    symbol_table_insert(symbol);
    return 0;

    error:
    return -1;
}

int handle_directive_line(Context *context) {
    const char* line = context->line_descriptor->line;
    DirectiveDescriptor *descriptor;
    const char* sentence;
    char *operands;
    int result;
    bool is_label = context->line_descriptor->is_label;
    bool is_first_pass = context->assembler_context->is_first_pass;
    descriptor = get_directive_descriptor(context);

    if (descriptor == NULL && is_first_pass) {
        fprintf(stderr, ERR_INVALID_SENTENCE, line);
        goto error;
    }
    if (is_label && is_first_pass) {
        descriptor->handle_label(context);
    }

    sentence = context->line_descriptor->sentence;
    operands = get_operands(sentence);
    context->line_descriptor->operands = operands;

    result = descriptor->generate(context);
    return result;

    error:
    return -1;
}

int handle_instruction_line(Context *context) {
    const char* line = context->line_descriptor->line;
    bool is_label = context->line_descriptor->is_label;
    bool is_first_pass = context->assembler_context->is_first_pass;
    OperationDescriptor* descriptor = get_operation_descriptor(context);
    OperandDescriptor* operandDescriptors;
    const char* sentence;
    char* operands;
    int result;

    if (descriptor == NULL && is_first_pass) {
        fprintf(stderr, ERR_INVALID_SENTENCE, line);
        goto error;
    }

    if (is_label && is_first_pass) {
        descriptor->handle_label(context);
    }

    sentence = context->line_descriptor->sentence;
    operands = get_operands(sentence);
    context->line_descriptor->operands = operands;

    operandDescriptors = get_operand_descriptors(context);
    if (operandDescriptors == NULL && context->instruction->operand_count != 0) {
        goto error;
    }

    result = descriptor->generate(context);
    return result;

    error:
    return -1;
}

int handle_line(Context* context) { /* Handle a line in the assembly code */
    const char* line = context->line_descriptor->line;
    bool is_label;
    bool is_first_pass = context->assembler_context->is_first_pass;
    char sentence[MAX_LINE_LENGTH];
    char label[MAX_LABEL_LENGTH];
    SENTENCE_TYPE sentence_type;

    if (line[0] == '\n' || line[0] == '\0') { /* Skip empty lines */
        return 0;
    }

    is_label = is_label_in_line(line);
    if(is_label) { /* If there is a label, split it from the sentence */
        split_label_and_sentence(line, label, sentence);
    }
    else {
        strcpy(sentence, line);
        trim_whitespace(sentence); /* Remove whitespace from the sentence */
    }

    sentence_type = get_sentence_type(sentence); /* Get the sentence type */

    context->line_descriptor->label = label;
    context->line_descriptor->sentence = sentence;
    context->line_descriptor->is_label = is_label;

    /* Handle the sentence according to its type */
    if (sentence_type == DEFINE_SENTENCE){
        return handle_define_line(context);
    }
    if (sentence_type == DIRECTIVE_SENTENCE) {
        return handle_directive_line(context);
    }
    if (sentence_type == INSTRUCTION_SENTENCE) {
        return handle_instruction_line(context);
    }
    if (is_first_pass) {
        fprintf(stderr, ERR_INVALID_SENTENCE, line); /* The line is invalid so we show an error if it's the first pass */
    }
    return -1; /* The line is invalid and we error */
}


