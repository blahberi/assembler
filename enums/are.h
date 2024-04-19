//
// Author: Eitan H. .
//

#ifndef ASSEMBLER_ARE_H
#define ASSEMBLER_ARE_H

// Enum for ARE (Absolute, Relocatable, External) bits
typedef enum {
    ABSOLUTE = 0,
    RELOCATABLE = 2,
    EXTERNAL = 1
} ARE;

#endif //ASSEMBLER_ARE_H
