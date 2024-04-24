//
// Author: Eitan H.
//


#include "../context/context.h"
#include "../utils/utils.h"
#include "../operand_to_machine_code.h"
#include "../utils/assembly_strings.h"
#include "../utils/errors.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

OperandDescriptor* get_operand_descriptors(Context *context) {
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

    OperandDescriptor* descriptors = malloc((count) * sizeof(OperandDescriptor)); // Allocate an array of OperandDescriptor objects
    int i;
    for (i = 0; i < count; i++) {
        // Trim leading and trailing whitespace
        trim_whitespace(operand_strings[i]);

        // Create a new OperandDescriptor
        descriptors[i].operand = strdup(operand_strings[i]); // Set the operand field directly
        if (get_addr_mode(&descriptors[i]) != 0) {
            goto error;
        }

    }


    // Free the operand strings
    for (int i = 0; i < count; i++) {
        free(operand_strings[i]);
    }
    free(operand_strings);

    context->instruction->operands = descriptors;
    context->instruction->operand_count = count;
    return descriptors;

    error:
    for (int i = 0; i < count; i++) {
        free(operand_strings[i]);
    }
    free(operand_strings);
    free(descriptors);
    return NULL;
}

int get_addr_mode(OperandDescriptor *descriptor) {
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
    fprintf(stderr, ERR_INVALID_OPERAND, operand);
    return -1;
}