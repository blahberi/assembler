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

struct OperandDescriptor { /* Information about the operand */
    const char* operand;  /* The operand */
    ADDR_MODE addr_mode; /* Addressing mode */
    bool is_dest; /* Is this the destination operand? */
    OperandGenerator *generate; /* Function to generate the operand */
};

OperandDescriptor* get_operand_descriptors(struct Context *context); /* Get the operand descriptors */
int get_addr_mode(OperandDescriptor *descriptor, struct Context *context); /* Get the addressing mode of an operand */


#endif /* ASSEMBLER_OPERAND_DESCRIPTOR_H */
