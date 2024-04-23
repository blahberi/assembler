//
// Author: Eitan H.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../assembler_context.h"
#include "../utils/assembly_strings.h"
#include "../utils/utils.h"
#include "../descriptors/directive_descriptor.h"
#include "../descriptors/operation_descriptor.h"
#include "../symbol_table/global_symbol_table.h"
#include "../utils/errors.h"
#include "../utils/error_checking.h"

int handle_define_line(const char* line, const char* sentence, bool is_label, const AssemblerContext *context) {
    if (!context->is_first_pass) {
        return 0;
    }
    if (is_label){
        fprintf(stderr, ERR_DEFINE_GOT_LABEL, line);
        return -1;
    }

    char* operands = get_operands(sentence);

    char* label = strtok(operands, "=");
    trim_whitespace(label);

    char* value_str = strtok(NULL, "=");
    trim_whitespace(value_str);

    if (label == NULL || value_str == NULL) {
        fprintf(stderr, ERR_DEFINE_DIDNT_GET_VALUE, line);
        return -1;
    }

    if (check_label_err(line, label, context) != 0) {
        return -1;
    }

    int value;
    if (get_value_signed(value_str, &value) != 0) {
        fprintf(stderr, ERR_INVALID_DEFINE_VALUE, line);
        return -1;
    }

    Symbol *symbol = construct_symbol(label, MDEFINE_LABEL, value, false);
    symbol_table_insert(symbol);
    free(operands);
    return 0;
}

int handle_directive_line(const char* line, const char* sentence, bool is_label, const char* label, AssemblerContext *context, Word *data_words) {
    DirectiveDescriptor* descriptor = get_directive_descriptor(sentence);
    if (descriptor == NULL) {
        fprintf(stderr, ERR_INVALID_SENTENCE, line);
        return -1;
    }

    if (is_label && context->is_first_pass) {
        descriptor->handle_label(label, line, context);
    }

    char* operands = get_operands(sentence);

    int result = descriptor->generate(descriptor, operands, line, context, data_words);
    free(descriptor);
    free(operands);

    return result;
}

int handle_instruction_line(const char* line, const char* sentence, bool is_label, const char* label, AssemblerContext *context, Word *instruction_words) {
    OperationDescriptor *descriptor = get_operation_descriptor(sentence);
    if (descriptor == NULL) {
        fprintf(stderr, ERR_INVALID_SENTENCE, line);
        return -1;
    }

    if (is_label && context->is_first_pass) {
        descriptor->handle_label(label, line, context);
    }

    char* operands = get_operands(sentence);
    int size = 0;
    if (operands != NULL) {
        size = comma_seperated_list_length(operands);
    }

    OperandDescriptor *operandDescriptors = get_operand_descriptors(operands);

    int result = descriptor->generate(descriptor, operandDescriptors, line, context, instruction_words);

    for (int i = 0; i < size; i++) {
        free((void*)(operandDescriptors + i)->operand);
    }
    free(operandDescriptors);
    free(operands);
    free(descriptor);

    return result;
}

int handle_line(const char* line, AssemblerContext *context, Word *instruction_words, Word *data_words) {
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
    if (sentence_type == DEFINE_SENTENCE){
        return handle_define_line(line, sentence, is_label, context);
    }
    if (sentence_type == DIRECTIVE_SENTENCE) {
        return handle_directive_line(line, sentence, is_label, label, context, data_words);
    }
    if (sentence_type == INSTRUCTION_SENTENCE) {
        return handle_instruction_line(line, sentence, is_label, label, context, instruction_words);
    }
    fprintf(stderr, ERR_INVALID_SENTENCE, line);
    return -1;
}


