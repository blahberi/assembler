//
// Author: Eitan H. .
//

#ifndef ASSEMBLER_OPERATION_DESCRIPTOR_H
#define ASSEMBLER_OPERATION_DESCRIPTOR_H

#include <stdint.h>
#include "../machine_code_generator/instruction_to_machine_code.h"
#include "operand_descriptor.h"

// Enum for operation codes
typedef enum {
    MOV = 0, // Move
    CMP,     // Compare
    ADD,     // Add
    SUB,     // Subtract
    NOT,     // Logical NOT
    CLR,     // Clear
    LEA,     // Load Effective Address
    INC,     // Increment
    DEC,     // Decrement
    JMP,     // Jump
    BNE,     // Branch if Not Equal
    RED,     // Read
    PRN,     // Print
    JSR,     // Jump to Subroutine
    RTS,     // Return from Subroutine
    HLT      // Halt
} OPCODE;

typedef struct OperationDescriptor OperationDescriptor;

typedef int (*InstructionGenerator)(OperationDescriptor*, OperandDescriptor*, OperandDescriptor*, InstructionWord*);

struct OperationDescriptor {
    OPCODE opcode;
    InstructionGenerator generate;
};

#endif //ASSEMBLER_OPERATION_DESCRIPTOR_H
