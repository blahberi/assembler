/*
 Author: Eitan H.
*/


#include <string.h>
#include "line_list.h"
#include "../../memory_allocator/memory_allocator.h"

LineList* construct_line_list() { /* Construct a new line list */
    LineList* list = (LineList*) malloc_track_global(sizeof(LineList)); /* Allocate memory for the list */
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void add_line(LineList* this, const char* line) { /* Add a line to the list */
    LineNode* new_node = (LineNode*) malloc_track_global(sizeof(LineNode)); /* Allocate memory for the new node */
    new_node->line = (char*) malloc_track_global(strlen(line) + 1); /* Allocate memory for the line */
    strcpy(new_node->line, line); /* Copy the line to the new node */
    new_node->next = NULL;
    if (this->head == NULL) {
        this->head = new_node; /* Update the head */
        this->tail = new_node; /* Update the tail */
    } else {
        this->tail->next = new_node; /* Add the new node to the end of the list */
        this->tail = new_node; /* Update the tail */
    }
}
