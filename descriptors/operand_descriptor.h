//
// Author: Eitan H. .
//

#ifndef ASSEMBLER_OPERAND_DESCRIPTOR_H
#define ASSEMBLER_OPERAND_DESCRIPTOR_H

#include <stdbool.h>
#include "../words/instruction_word.h"
#include "../addressing_mode/addressing_mode.h"


typedef struct operand_descriptor OperandDescriptor;

typedef int (*OperandGenerator)(OperandDescriptor*, InstructionWord*);

struct operand_descriptor {
    const char* operand;
    ADDR_MODE addr_mode;
    bool is_dest;
    OperandGenerator generate;
};


#endif //ASSEMBLER_OPERAND_DESCRIPTOR_H
