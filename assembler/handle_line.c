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
    // get number of operands

    descriptor->generate(descriptor, operands, context, data_words);
    free(descriptor);
    free(operands);
}

void handle_instruction_line(const char* sentence, bool is_label, const char* label, AssemblerContext *context, Word *instruction_words) {
    OperationDescriptor *descriptor = get_operation_descriptor(sentence);
    if (descriptor == NULL) {
        fprintf(stderr, "Error: Invalid directive\n");
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
        free((operandDescriptors + i)->operand);
    }
    free(operandDescriptors);
    free(operands);
    free(descriptor);
}

void handle_line(const char* line, AssemblerContext *context, Word *instruction_words, Word *data_words) {
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

    if (sentence_type == DIRECTIVE_SENTENCE) {
        handle_directive_line(sentence, is_label, label, context, data_words);
    }
    if (sentence_type == INSTRUCTION_SENTENCE) {
        handle_instruction_line(sentence, is_label, label, context, instruction_words);
    }
}


