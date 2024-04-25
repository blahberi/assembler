/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_OPERAND_DESCRIPTOR_H
#define ASSEMBLER_OPERAND_DESCRIPTOR_H

#include <stdbool.h>
#include "../enums.h"

struct Context;

typedef struct OperandDescriptor OperandDescriptor;
typedef int (OperandGenerator)(OperandDescriptor*, struct Context *context);

struct OperandDescriptor {
    const char* operand;
    ADDR_MODE addr_mode;
    bool is_dest;
    OperandGenerator *generate;
};

OperandDescriptor* get_operand_descriptors(struct Context *context);
int get_addr_mode(OperandDescriptor *descriptor, struct Context *context);


#endif /* ASSEMBLER_OPERAND_DESCRIPTOR_H */
