/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_NODE_H
#define ASSEMBLER_NODE_H

typedef struct Node {
    const char *key;
    void* value;
    struct Node *next;
} Node;

#endif /* ASSEMBLER_NODE_H */
