/*
 Author: Eitan H.
*/

#include "extern_label_list.h"
#include <string.h>
#include <stdio.h>
#include "../../errors.h"
#include "../../memory_allocator/memory_allocator.h"


void add(ExternalLabelList* this, ExternalLabelUsage* usage) { /* Add an external label usage to the list */
    ExternalLabelNode* new_node = malloc_track_global(sizeof(ExternalLabelNode));
    if (!new_node) {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
        return;
    }
    new_node->usage = usage;
    new_node->next = NULL;
    if (this->head == NULL) {
        this->head = new_node;
    } else {
        ExternalLabelNode* current = this->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

ExternalLabelUsage* get(ExternalLabelList* this, const char* label) { /* Get an external label usage from the list */
    ExternalLabelNode* current = this->head;
    while (current != NULL) {
        if (strcmp(current->usage->label, label) == 0) {
            return current->usage;
        }
        current = current->next;
    }
    return NULL;
}

ExternalLabelList* construct_external_label_list() { /* Construct an external label list */
    ExternalLabelList* table = malloc_track_global(sizeof(ExternalLabelList));
    table->head = NULL;
    table->add = add;
    table->get = get;
    return table;
}
