//
// Author: Eitan H.
//

#ifndef ASSEMBLER_ASSEMBLER_CONTEXT_H
#define ASSEMBLER_ASSEMBLER_CONTEXT_H

#include <stdbool.h>

typedef struct {
    int IC; // Instruction counter
    int DC; // Data counter
    bool is_first_pass;
} AssemblerContext;

#endif //ASSEMBLER_ASSEMBLER_CONTEXT_H
