/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_LINE_LIST_H
#define ASSEMBLER_LINE_LIST_H

typedef struct LineNode{
    char* line;
    struct LineNode* next;
} LineNode;

typedef struct LineList {
    LineNode* head;
    LineNode* tail;
} LineList;

LineList* construct_line_list();
void add_line(LineList* this, const char* line);

#endif /* ASSEMBLER_LINE_LIST_H */
