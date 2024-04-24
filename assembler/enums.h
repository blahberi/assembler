//
// Author: Eitan H.
//

#ifndef ASSEMBLER_ENUMS_H
#define ASSEMBLER_ENUMS_H

// Enum for addressing modes
typedef enum {
    IMMEDIATE = 0, // Immediate value
    DIRECT,        // Direct memory address
    INDEX,         // Indexed addressing mode
    REGISTER       // Register direct
} ADDR_MODE;

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

typedef enum {
    ABSOLUTE = 0,
    RELOCATABLE = 2,
    EXTERNAL = 1
} ARE;

typedef enum {
    DATA_DIRECTIVE,
    STRING_DIRECTIVE,
    ENTRY_DIRECTIVE,
    EXTERN_DIRECTIVE

} DIRECTIVE_TYPE;

typedef enum {
    DEFINE_SENTENCE,
    DIRECTIVE_SENTENCE,
    INSTRUCTION_SENTENCE
} SENTENCE_TYPE;


#endif //ASSEMBLER_ENUMS_H
