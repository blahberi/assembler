//
// Author: Eitan H.
//

#ifndef ASSEMBLER_EXTERN_LABEL_LIST_H
#define ASSEMBLER_EXTERN_LABEL_LIST_H

#include "extern_label_node.h"

typedef struct extern_label_list ExternalLabelList;

struct extern_label_list{
    ExternalLabelNode* head;
    void (*add)(ExternalLabelList* this, ExternalLabelUsage* usage);
    void (*remove)(ExternalLabelList* this, const char* label);
    ExternalLabelUsage* (*get)(ExternalLabelList* this, const char* label);
    void (*free)(ExternalLabelList* list);
};

ExternalLabelList* construct_external_label_list();

#endif //ASSEMBLER_EXTERN_LABEL_LIST_H
