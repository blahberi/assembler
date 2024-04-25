/*
 Author: Eitan H.
*/

#include <stdlib.h>
#include <stdio.h>
#include "../context/context.h"
#include "../utils/assembly_strings.h"
#include "../utils/utils.h"
#include "../instruction_to_machine_code.h"
#include "../../errors.h"
#include "../../memory_allocator/memory_allocator.h"

OperationDescriptor* get_operation_descriptor(Context *context){
    const char* sentence = context->line_descriptor->sentence;
    char* operation_str = get_sentence_start(sentence);
    trim_whitespace(operation_str);
    OPCODE opcode;
    InstructionGenerator *generate = NULL;
    LabelHandler *handle_label = handle_label_instruction;

    opcode = find_operation(operation_str);
    generate = get_instruction_generator(opcode);

    OperationDescriptor* descriptor = (OperationDescriptor*) malloc_track(sizeof(struct operation_descriptor));
    if (!descriptor) {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }
    descriptor->opcode = opcode;
    descriptor->generate = generate;
    descriptor->handle_label = handle_label;
    context->instruction->operation = descriptor;

    return descriptor;
}
