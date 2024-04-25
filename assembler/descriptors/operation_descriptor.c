/*
 Author: Eitan H.
*/

#include <stdio.h>
#include "../context/context.h"
#include "../utils/assembly_strings.h"
#include "../instruction_to_machine_code.h"
#include "../../errors.h"
#include "../../memory_allocator/memory_allocator.h"

OperationDescriptor* get_operation_descriptor(Context *context){ /* Get the operation descriptor */
    const char* sentence = context->line_descriptor->sentence;
    char* operation_str = get_sentence_start(sentence);
    OPCODE opcode;
    InstructionGenerator *generate; /* Function to generate the instruction machine code */
    LabelHandler *handle_label; /* Function to handle the label i.e put it in the symbol table */
    OperationDescriptor *descriptor;

    trim_whitespace(operation_str); /* Remove whitespace from the operation string */
    handle_label = handle_label_instruction; /* set the label handler to the instruction label handler */
    opcode = find_operation(operation_str);
    generate = get_instruction_generator(opcode); /* Get the instruction generator */

    descriptor = (OperationDescriptor*) malloc_track(sizeof(OperationDescriptor)); /* Allocate memory for the descriptor */

    /* Set the descriptor fields */
    descriptor->opcode = opcode;
    descriptor->generate = generate;
    descriptor->handle_label = handle_label;
    context->instruction->operation = descriptor;

    return descriptor;
}
