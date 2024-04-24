//
// Author: Eitan H.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../context/assembler_context.h"
#include "../utils/assembly_strings.h"
#include "../utils/utils.h"
#include "../descriptors/directive_descriptor.h"
#include "../descriptors/operation_descriptor.h"
#include "../symbol_table/global_symbol_table.h"
#include "../utils/errors.h"
#include "../utils/error_checking.h"
#include "../context/context.h"

int handle_define_line(Context *context) {
    if (!context->assembler_context->is_first_pass) {
        return 0;
    }
    if (context->line_descriptor->is_label) {
        fprintf(stderr, ERR_DEFINE_GOT_LABEL, context->line_descriptor->line);
        return -1;
    }

    const char* operands = get_operands(context);
    char* label = strtok(operands, "=");
    trim_whitespace(label);

    char* value_str = strtok(NULL, "=");
    trim_whitespace(value_str);

    if (label == NULL || value_str == NULL) {
        fprintf(stderr, ERR_DEFINE_DIDNT_GET_VALUE, context->line_descriptor->line);
        return -1;
    }

    if (check_label_err(label, context) != 0) {
        return -1;
    }

    int value;
    if (get_value_signed(value_str, &value) != 0) {
        fprintf(stderr, ERR_INVALID_DEFINE_VALUE, context->line_descriptor->line);
        return -1;
    }

    Symbol *symbol = construct_symbol(label, MDEFINE_LABEL, value, false);
    symbol_table_insert(symbol);
    free(operands);
    return 0;
}

int handle_directive_line(Context *context) {
    const char* line = context->line_descriptor->line;
    bool is_label = context->line_descriptor->is_label;
    bool is_first_pass = context->assembler_context->is_first_pass;
    DirectiveDescriptor *descriptor = get_directive_descriptor(context);
    if (descriptor == NULL) {
        fprintf(stderr, ERR_INVALID_SENTENCE, line);
        return -1;
    }
    if (is_label && is_first_pass) {
        descriptor->handle_label(context);
    }

    get_operands(context);

    int result = descriptor->generate(context);
    return result;
}

int handle_instruction_line(Context *context) {
    const char* line = context->line_descriptor->line;
    bool is_label = context->line_descriptor->is_label;
    bool is_first_pass = context->assembler_context->is_first_pass;
    OperationDescriptor* descriptor = get_operation_descriptor(context);
    if (descriptor == NULL) {
        fprintf(stderr, ERR_INVALID_SENTENCE, line);
        return -1;
    }

    if (is_label && is_first_pass) {
        descriptor->handle_label(context);
    }

    char* operands = get_operands(context);
    int size = 0;
    if (operands != NULL) {
        size = comma_seperated_list_length(operands);
    }

    OperandDescriptor* operandDescriptors = get_operand_descriptors(context);

    int result = descriptor->generate(context);

    for (int i = 0; i < size; i++) {
        free((void*)(operandDescriptors + i)->operand);
    }
    free(operandDescriptors);
    free(operands);
    free(descriptor);

    return result;
}

int handle_line(Context* context) {
    const char* line = context->line_descriptor->line;
    if (line[0] == '\n' || line[0] == '\0') {
        return 0;
    }

    bool is_label = is_label_in_line(line);
    char sentence[MAX_LINE_LENGTH];
    char label[MAX_LABEL_LENGTH];
    if(is_label) {
        split_label_and_sentence(line, label, sentence);
    }
    else {
        strcpy(sentence, line);
        trim_whitespace(sentence);
    }

    SENTENCE_TYPE sentence_type = get_sentence_type(sentence);

    context->line_descriptor->label = label;
    context->line_descriptor->sentence = sentence;
    context->line_descriptor->is_label = is_label;

    if (sentence_type == DEFINE_SENTENCE){
        return handle_define_line(context);
    }
    if (sentence_type == DIRECTIVE_SENTENCE) {
        return handle_directive_line(context);
    }
    if (sentence_type == INSTRUCTION_SENTENCE) {
        return handle_instruction_line(context);
    }
    fprintf(stderr, ERR_INVALID_SENTENCE, line);
    return -1;
}


