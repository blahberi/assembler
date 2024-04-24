//
// Author: Eitan H.
//

#ifndef ASSEMBLER_OPERAND_DESCRIPTOR_H
#define ASSEMBLER_OPERAND_DESCRIPTOR_H

#include <stdbool.h>
#include "../enums.h"

typedef struct context Context;

typedef struct operand_descriptor OperandDescriptor;

typedef int (OperandGenerator)(OperandDescriptor*, Context *context);

struct operand_descriptor {
    const char* operand;
    ADDR_MODE addr_mode;
    bool is_dest;
    OperandGenerator *generate;
};

OperandDescriptor* get_operand_descriptors(Context *context);
int get_addr_mode(OperandDescriptor *descriptor);


#endif //ASSEMBLER_OPERAND_DESCRIPTOR_H
