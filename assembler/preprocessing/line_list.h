//
// Author: Eitan H.
//

#ifndef ASSEMBLER_LINE_LIST_H
#define ASSEMBLER_LINE_LIST_H

typedef struct LineNode{
    char* line;
    struct LineNode* next;
} LineNode;

typedef struct LineList {
    LineNode* head;
} LineList;

LineList* construct_line_list();

#endif //ASSEMBLER_LINE_LIST_H
