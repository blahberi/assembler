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

void remove_extern_label_usage(const char *label) {
    EXTERN_LIST->remove(EXTERN_LIST, label);
}

ExternalLabelUsage *get_extern_label_usage(const char *label) {
    return EXTERN_LIST->get(EXTERN_LIST, label);
}

void free_extern_list() {
    EXTERN_LIST->free(EXTERN_LIST);
}

void update_extern_list_address() {
    ExternalLabelNode *current = EXTERN_LIST->head;
    while (current != NULL) {
        current->usage->memory_address += 100;
        current = current->next;
    }
}

void write_extern_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    ExternalLabelNode* current = EXTERN_LIST->head;
    while (current != NULL) {
        fprintf(file, "%s\t%04d\n", current->usage->label, current->usage->memory_address);
        current = current->next;
    }

    fclose(file);
}