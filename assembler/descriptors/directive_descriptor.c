/*
 Author: Eitan H.
*/

#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "../context/context.h"
#include "../utils/assembly_strings.h"
#include "../utils/utils.h"
#include "../directive_to_machine_code.h"
#include "../../errors.h"
#include "../../memory_allocator/memory_allocator.h"

DirectiveDescriptor* get_directive_descriptor(Context* context) { /* Get the directive descriptor*/
    const char* sentence = context->line_descriptor->sentence;
    char* directive_str = get_sentence_start(sentence); /* Get the directive string */
    DirectiveGenerator *generate; /* Function to generate the directive machine code */
    LabelHandler *handle_label; /* Function to handle the label i.e put it in the symbol table */
    DIRECTIVE_TYPE type;
    DirectiveDescriptor *descriptor;

    trim_whitespace(directive_str); /* Remove whitespace from the directive string */
    generate= NULL;
    handle_label = NULL;
    type = find_directive(directive_str); /* Get the directive type */
    switch (type) {
        case DATA_DIRECTIVE:
            generate = generate_data_directive;
            handle_label = handle_label_data;
            break;
        case STRING_DIRECTIVE:
            generate = generate_string_directive;
            handle_label = handle_label_data; /* Same as data directive */
            break;
        case ENTRY_DIRECTIVE:
            generate = generate_entry_directive;
            handle_label = handle_label_entry; /* Just warn that label is not used */
            break;
        case EXTERN_DIRECTIVE:
            generate = generate_extern_directive;
            handle_label = handle_label_extern; /* Just warn that label is not used */
            break;
    }
    descriptor = (DirectiveDescriptor*) malloc_track(sizeof(struct DirectiveDescriptor)); /* Allocate memory for the descriptor */
    descriptor->type = type; /* Set the type */
    descriptor->generate = generate; /* Set the generate function */
    descriptor->handle_label = handle_label; /* Set the handle label function */

    context->directive = descriptor; /* Add the descriptor to the context */
    return descriptor;
}
