/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_EXTERN_LABEL_NODE_H
#define ASSEMBLER_EXTERN_LABEL_NODE_H

#include "extern_label_usage.h"

typedef struct external_label_node ExternalLabelNode;

struct external_label_node { /* External label node */
    ExternalLabelUsage* usage; /* The external label usage */
    ExternalLabelNode* next; /* The next node */
};

#endif /* ASSEMBLER_EXTERN_LABEL_NODE_H */
