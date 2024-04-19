//
// Author: Eitan H. .
//

#ifndef ASSEMBLER_OPERAND_WORDS_H
#define ASSEMBLER_OPERAND_WORDS_H

typedef struct {
    unsigned int ARE : 2;
    unsigned int VALUE: 12;
} ValueWord;

typedef struct {
    unsigned int ARE: 2;
    unsigned int DEST: 3;
    unsigned int SRC: 3;
} RegisterWord;

typedef struct  {
    ValueWord address_word; // The label's address
    ValueWord index_word; // The index, ARE = ABSOLUTE
} IndexMachineCode;

#endif //ASSEMBLER_OPERAND_WORDS_H
