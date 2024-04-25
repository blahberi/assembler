//
// Author: Eitan H.
//


#include <stdio.h>
#include <string.h>
#include "line_list.h"
#include "../../errors.h"
#include "../../memory_tracker/global_memory_tracker.h"


LineList* construct_line_list() {
    LineList* list = (LineList*) malloc_track_global(sizeof(LineList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void add_line(LineList* this, const char* line) {
    LineNode* new_node = (LineNode*) malloc_track_global(sizeof(LineNode));
    new_node->line = (char*) malloc_track_global(strlen(line) + 1);
    strcpy(new_node->line, line);
    new_node->next = NULL;
    if (this->head == NULL) {
        this->head = new_node;
        this->tail = new_node;
    } else {
        this->tail->next = new_node;
        this->tail = new_node;
    }
}