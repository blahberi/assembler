//
// Author: Eitan H.
//

#include <stdio.h>
#include "extern_label_list.h"

ExternalLabelList *EXTERN_LIST;

void init_extern_list() {
    EXTERN_LIST = construct_external_label_list();
}

void add_extern_label_usage(const char *label, int memory_address) {
    ExternalLabelUsage *usage = construct_external_label_usage(label, memory_address);
    EXTERN_LIST->add(EXTERN_LIST, usage);
}

ExternalLabelUsage *get_extern_label_usage(const char *label) {
    return EXTERN_LIST->get(EXTERN_LIST, label);
}

void update_extern_list_address() {
    ExternalLabelNode *current = EXTERN_LIST->head;
    while (current != NULL) {
        current->usage->memory_address += 100;
        current = current->next;
    }
}

void write_extern_file(const char *filepath) {
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Unable to open file %s\n", filepath);
        return;
    }

    ExternalLabelNode* current = EXTERN_LIST->head;
    while (current != NULL) {
        fprintf(file, "%s %04d\n", current->usage->label, current->usage->memory_address);
        current = current->next;
    }

    fclose(file);
}