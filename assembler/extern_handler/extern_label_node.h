//
// Author: Eitan H.
//

#ifndef ASSEMBLER_EXTERN_LABEL_NODE_H
#define ASSEMBLER_EXTERN_LABEL_NODE_H

#include "extern_label_usage.h"

typedef struct external_label_node ExternalLabelNode;

struct external_label_node {
    ExternalLabelUsage* usage;
    ExternalLabelNode* next;
};

#endif //ASSEMBLER_EXTERN_LABEL_NODE_H
