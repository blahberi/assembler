/*
 Author: Eitan H.
*/

#include <stdio.h>
#include <stdbool.h>
#include "extern_label_list.h"
#include "extern_handler.h"

ExternalLabelList *EXTERN_LIST;

void init_extern_list(void) { /* Initialize the extern list */
    EXTERN_LIST = construct_external_label_list();
}

void add_extern_label_usage(const char *label, int memory_address) { /* Add an external label usage to the list */
    ExternalLabelUsage *usage = construct_external_label_usage(label, memory_address);
    EXTERN_LIST->add(EXTERN_LIST, usage);
}

ExternalLabelUsage *get_extern_label_usage(const char *label) { /* Get an external label usage from the list */
    return EXTERN_LIST->get(EXTERN_LIST, label);
}

void update_extern_list_address(void) { /* Update the memory address of the external labels */
    ExternalLabelNode *current = EXTERN_LIST->head;
    while (current != NULL) {
        current->usage->memory_address += 100;
        current = current->next;
    }
}

bool is_extern() { /* Check if there is an extern in the list */
    return EXTERN_LIST->head != NULL;
}

void write_extern_file(const char *filepath) { /* Write the extern file */
    if (!is_extern()) {
        return;
    }
    ExternalLabelNode* current;
    FILE *file = fopen(filepath, "w");

    if (file == NULL) {
        printf("Unable to open file %s\n", filepath);
        return;
    }

    current = EXTERN_LIST->head;
    while (current != NULL) {
        fprintf(file, "%s %04d\n", current->usage->label, current->usage->memory_address);
        current = current->next;
    }

    fclose(file);
}
