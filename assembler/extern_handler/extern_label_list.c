//
// Author: Eitan H.
//

#include "extern_label_list.h"
#include <stdlib.h>
#include <string.h>
#include "../../config.h"


void add(ExternalLabelList* this, ExternalLabelUsage* usage) {
    ExternalLabelNode* new_node = malloc(sizeof(ExternalLabelNode));
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

void remove(ExternalLabelList* this, const char* label) {
    ExternalLabelNode* current = this->head;
    ExternalLabelNode* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->usage->label, label) == 0) {
            if (prev == NULL) {
                this->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->usage->label);
            free(current->usage);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

ExternalLabelUsage* get(ExternalLabelList* this, const char* label) {
    ExternalLabelNode* current = this->head;
    while (current != NULL) {
        if (strcmp(current->usage->label, label) == 0) {
            return current->usage;
        }
        current = current->next;
    }
    return NULL;
}

void free_list(ExternalLabelList* list) {
    ExternalLabelNode* current = list->head;
    while (current != NULL) {
        ExternalLabelNode* next = current->next;
        free(current->usage->label);
        free(current->usage);
        free(current);
        current = next;
    }
    free(list);
}

ExternalLabelList* construct_external_label_list() {
    ExternalLabelList* table = malloc(sizeof(ExternalLabelList));
    table->head = NULL;
    table->add = add;
    table->remove = remove;
    table->get = get;
    table->free = free_list;
    return table;
}
