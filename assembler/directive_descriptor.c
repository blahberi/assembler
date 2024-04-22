//
// Author: Eitan H.
//


#include <tchar.h>
#include "directive_descriptor.h"
#include "assembly_strings.h"
#include "../utils/utils.h"
#include "directive_to_machine_code.h"
#include <stdlib.h>

DirectiveDescriptor* get_directive_descriptor(const char* sentence) {
    char* directive_str = get_sentence_start(sentence);
    trim_whitespace(directive_str);
    DirectiveGenerator *generate= NULL;
    LabelHandler *handle_label = NULL;
    DIRECTIVE_TYPE type = 0;
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
    DirectiveDescriptor* descriptor = (DirectiveDescriptor*) malloc(sizeof(struct directive_descriptor));
    descriptor->type = type;
    descriptor->generate = generate;
    descriptor->handle_label = handle_label;
    return descriptor;
}