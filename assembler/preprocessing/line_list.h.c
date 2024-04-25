//
// Author: Eitan H.
//


#include <stdio.h>
#include <string.h>
#include "line_list.h"
#include "../../errors.h"
#include "../../memory_tracker/scope_memory_tracker.c.h"

void add_line(LineList* this, const char* line) {
    LineNode* new_node = (LineNode*) malloc_track(sizeof(LineNode));
    if (!new_node) {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
        return;
    }
    new_node->line = (char*) malloc_track(strlen(line) + 1);
    if (!new_node->line) {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
        return;
    }
    strcpy(new_node->line, line);
    new_node->next = this->head;
    this->head = new_node;
}