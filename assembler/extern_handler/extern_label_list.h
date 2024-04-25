/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_EXTERN_LABEL_LIST_H
#define ASSEMBLER_EXTERN_LABEL_LIST_H

#include "extern_label_node.h"

typedef struct ExternLabelList ExternalLabelList;

struct ExternLabelList { /* External label list */
    ExternalLabelNode* head; /* The head of the linked list */
    void (*add)(ExternalLabelList* this, ExternalLabelUsage* usage); /* A function to add an external label usage */
    ExternalLabelUsage* (*get)(ExternalLabelList* this, const char* label); /* Get an external label usage */
};

ExternalLabelList* construct_external_label_list();

#endif /* ASSEMBLER_EXTERN_LABEL_LIST_H */
