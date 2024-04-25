/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_LINE_LIST_H
#define ASSEMBLER_LINE_LIST_H

typedef struct LineNode{ /* Represents a node in a line list */
    char* line;
    struct LineNode* next;
} LineNode;

typedef struct LineList { /* Represents a list of lines */
    LineNode* head;
    LineNode* tail;
} LineList;

LineList* construct_line_list(); /* Construct a new line list */
void add_line(LineList* this, const char* line); /* Add a line to the list */

#endif /* ASSEMBLER_LINE_LIST_H */
