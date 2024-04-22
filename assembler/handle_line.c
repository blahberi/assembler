//
// Author: Eitan H.
//

#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include "assembler_context.h"
#include "assembly_strings.h"
#include "../config.h"
#include "../utils/utils.h"
#include "sentence_type.h"
#include "directive_descriptor.h"
#include "operation_descriptor.h"
#include "../symbol_table/symbol.h"
#include "../symbol_table/global_symbol_table.h"

void handle_define_line(const char* sentence, bool is_label, const AssemblerContext *context) {
    if (!context->is_first_pass) {
        return;
    }
    if (is_label){
        fprintf(stderr, "Error: Label is not allowed for .define directive\n");
        exit(EXIT_FAILURE); // TODO: Handle error
    }

    char* operands = get_operands(sentence);
    char* label = strtok(operands, "=");
    trim_whitespace(label);
    char* value_str = strtok(NULL, "=");
    trim_whitespace(value_str);
    if (label == NULL || value_str == NULL) {
        fprintf(stderr, "Error: .define must receive a label and a value_str\n");
        exit(EXIT_FAILURE); // TODO: Handle error
    }
    check_label_and_error(label);
    if (!is_number_signed(value_str)) {
        fprintf(stderr, "Error: .define value_str must be a number\n");
        exit(EXIT_FAILURE); // TODO: Handle error
    }
    int value = atoi(value_str);

    Symbol *symbol = construct_symbol(label, MDEFINE_LABEL, value, false);
    symbol_table_insert(symbol);
    free(operands);
}

void handle_directive_line(const char* sentence, bool is_label, const char* label, AssemblerContext *context, Word *data_words) {
    DirectiveDescriptor* descriptor = get_directive_descriptor(sentence);
    if (descriptor == NULL) {
        fprintf(stderr, "Error: Invalid directive\n");
        exit(EXIT_FAILURE); // TODO: Handle error
    }

    if (is_label && context->is_first_pass) {
        descriptor->handle_label(label, context);
    }

    char* operands = get_operands(sentence);

    descriptor->generate(descriptor, operands, context, data_words);
    free(descriptor);
    free(operands);
}

void handle_instruction_line(const char* sentence, bool is_label, const char* label, AssemblerContext *context, Word *instruction_words) {
    OperationDescriptor *descriptor = get_operation_descriptor(sentence);
    if (descriptor == NULL) {
        fprintf(stderr, "Error: Invalid instruction\n");
        exit(EXIT_FAILURE); // TODO: Handle error
    }

    if (is_label && context->is_first_pass) {
        descriptor->handle_label(label, context);
    }

    char* operands = get_operands(sentence);
    int size = 0;
    if (operands != NULL) {
        size = comma_seperated_list_length(operands);
    }
    OperandDescriptor *operandDescriptors = get_operand_descriptors(operands);
    descriptor->generate(descriptor, operandDescriptors, context, instruction_words);
    for (int i = 0; i < size; i++) {
        free((void*)(operandDescriptors + i)->operand);
    }
    free(operandDescriptors);
    free(operands);
    free(descriptor);
}

void handle_line(const char* line, AssemblerContext *context, Word *instruction_words, Word *data_words) {
    if (line[0] == '\n' || line[0] == '\0') {
        return;
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
    if (sentence_type == -1) {
        fprintf(stderr, "Error: Invalid sentence type\n");
        exit(EXIT_FAILURE); // TODO: Handle error
    }
    if (sentence_type == DEFINE_SENTENCE){
        handle_define_line(sentence, is_label, context);
    }
    if (sentence_type == DIRECTIVE_SENTENCE) {
        handle_directive_line(sentence, is_label, label, context, data_words);
    }
    if (sentence_type == INSTRUCTION_SENTENCE) {
        handle_instruction_line(sentence, is_label, label, context, instruction_words);
    }
}


