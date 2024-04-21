//
// Author: Eitan H.
//

#ifndef ASSEMBLER_ADDRESSING_MODE_H
#define ASSEMBLER_ADDRESSING_MODE_H

#include "assembler_context.h"

typedef struct operand_descriptor OperandDescritor;

// Enum for addressing modes
typedef enum {
    IMMEDIATE = 0, // Immediate value
    DIRECT,        // Direct memory address
    INDEX,         // Indexed addressing mode
    REGISTER       // Register direct
} ADDR_MODE;

void get_addr_mode(struct operand_descriptor *, const AssemblerContext *context);

#endif //ASSEMBLER_ADDRESSING_MODE_H
