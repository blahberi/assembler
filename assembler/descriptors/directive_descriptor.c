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

DirectiveDescriptor* get_directive_descriptor(Context* context) {
    const char* sentence = context->line_descriptor->sentence;
    char* directive_str = get_sentence_start(sentence);
    DirectiveGenerator *generate;
    LabelHandler *handle_label;
    DIRECTIVE_TYPE type;
    DirectiveDescriptor *descriptor;

    trim_whitespace(directive_str);
    generate= NULL;
    handle_label = NULL;
    type = 0;
    if (strcmp(directive_str, ".data") == 0) {
        type = DATA_DIRECTIVE;
        generate = generate_data_directive;
        handle_label = handle_label_data;
    } else if (strcmp(directive_str, ".string") == 0) {
        type = STRING_DIRECTIVE;
        generate = generate_string_directive;
        handle_label = handle_label_data;
    } else if (strcmp(directive_str, ".entry") == 0) {
        type = ENTRY_DIRECTIVE;
        handle_label = handle_label_entry;
        generate = generate_entry_directive;
    } else if (strcmp(directive_str, ".extern") == 0) {
        type = EXTERN_DIRECTIVE;
        handle_label = handle_label_extern;
        generate = generate_extern_directive;
    }
    descriptor = (DirectiveDescriptor*) malloc_track(sizeof(struct DirectiveDescriptor));
    descriptor->type = type;
    descriptor->generate = generate;
    descriptor->handle_label = handle_label;

    context->directive = descriptor;
    return descriptor;
}
