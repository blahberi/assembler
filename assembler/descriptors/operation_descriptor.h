//
// Author: Eitan H.
//

#ifndef ASSEMBLER_OPERATION_DESCRIPTOR_H
#define ASSEMBLER_OPERATION_DESCRIPTOR_H

#include "operand_descriptor.h"
#include "../handlers/handle_label.h"

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

typedef struct operation_descriptor OperationDescriptor;

typedef int InstructionGenerator(Context *context);

struct operation_descriptor {
    OPCODE opcode;
    InstructionGenerator* generate;
    LabelHandler *handle_label;
};

OperationDescriptor* get_operation_descriptor(Context *context);

#endif //ASSEMBLER_OPERATION_DESCRIPTOR_H
