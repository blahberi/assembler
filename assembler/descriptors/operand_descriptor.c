//
// Author: Eitan H.
//


#include "../context/context.h"
#include "../utils/utils.h"
#include "../operand_to_machine_code.h"
#include "../utils/assembly_strings.h"
#include "../../errors.h"
#include "../../memory_tracker/scope_memory_tracker.c.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

OperandDescriptor* get_operand_descriptors(Context *context) {
    bool is_first_pass = context->assembler_context->is_first_pass;
    const char* line = context->line_descriptor->line;
    const char* operands = context->line_descriptor->operands;
    if (operands == NULL) {
        context->instruction->operand_count = 0;
        return NULL;
    }
    char** operand_strings = split_string_by_comma(operands);

    // Count the number of operand strings
    int count = 0;
    while (operand_strings[count] != NULL) {
        count++;
    }

    OperandDescriptor* descriptors = malloc_track((count) * sizeof(OperandDescriptor)); // Allocate an array of OperandDescriptor objects
    if (descriptors == NULL) {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
        goto error;
    }

    if (count != comma_seperated_list_length(operands)) {
        if (is_first_pass){
            fprintf(stderr, ERR_EMPTY_OPERAND, line);
        }
        goto error;
    }

    int i;
    for (i = 0; i < count; i++) {
        // Trim leading and trailing whitespace
        trim_whitespace(operand_strings[i]);

        if (operand_strings[i][0] == '\0') {
            if (is_first_pass) {
                fprintf(stderr, ERR_EMPTY_OPERAND, line);
            }
            goto error;
        }

        // Create a new OperandDescriptor
        descriptors[i].operand = strdup(operand_strings[i]); // Set the operand field directly
        track_pointer((void *) descriptors[i].operand);
        if (get_addr_mode(&descriptors[i], context) != 0) {
            goto error;
        }

    }

    context->instruction->operands = descriptors;
    context->instruction->operand_count = count;
    return descriptors;

    error:
    return NULL;
}

int get_addr_mode(OperandDescriptor *descriptor, Context *context) {
    bool is_first_pass = context->assembler_context->is_first_pass;
    const char* line = context->line_descriptor->line;
    const char* operand = descriptor->operand;
    if (operand[0] ==  '#') {
        descriptor->addr_mode = IMMEDIATE;
        descriptor->generate = generate_immediate_operand;
        return 0;
    }
    if (check_register(operand)){
        descriptor->addr_mode = REGISTER;
        descriptor->generate = generate_register_operand;
        return 0;
    }
    if (check_label(operand)) {
        descriptor->addr_mode = DIRECT;
        descriptor->generate = generate_direct_operand;
        return 0;
    }
    if (check_index_operand(operand)) {
        descriptor->addr_mode = INDEX;
        descriptor->generate = generate_index_operand;
        return 0;
    }
    if (is_first_pass) {
        fprintf(stderr, ERR_INVALID_OPERAND, operand, line);
    }
    return -1;
}