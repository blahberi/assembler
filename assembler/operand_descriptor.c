//
// Author: Eitan H.
//


#include "operand_descriptor.h"
#include "../utils/utils.h"

#include <stdlib.h>
#include <string.h>

OperandDescriptor* get_operand_descriptors(const char* operands) {
    if (operands == NULL) {
        return NULL;
    }
    char** operand_strings = split_string_by_comma(operands);

    // Count the number of operand strings
    int count = 0;
    while (operand_strings[count] != NULL) {
        count++;
    }

    OperandDescriptor* descriptors = malloc(count * sizeof(OperandDescriptor)); // Allocate an array of OperandDescriptor objects
    for (int i = 0; i < count; i++) {
        // Trim leading and trailing whitespace
        trim_whitespace(operand_strings[i]);

        // Create a new OperandDescriptor
        descriptors[i].operand = strdup(operand_strings[i]); // Set the operand field directly
        get_addr_mode(&descriptors[i]); // Pass a pointer to the OperandDescriptor
    }

    // Free the operand strings
    for (int i = 0; i < count; i++) {
        free(operand_strings[i]);
    }
    free(operand_strings);

    return descriptors;
}