/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_WORDS_H
#define ASSEMBLER_WORDS_H

#include "../config.h"

typedef struct word {
    unsigned int word : WORD_SIZE;
} Word;


typedef struct {
    unsigned int ARE : ARE_SIZE;
    unsigned int VALUE: VALUE_SIZE;
} ValueWord;

typedef struct {
    unsigned int ARE: ARE_SIZE;
    unsigned int DEST: REGISTER_SIZE;
    unsigned int SRC: REGISTER_SIZE;
} RegisterWord;

typedef struct  {
    ValueWord address_word; /* The label's address */
    ValueWord index_word; /* The index, ARE = ABSOLUTE */
} IndexMachineCode;

typedef struct  {
    unsigned int ARE : ARE_SIZE;
    unsigned int DEST : ADDRESING_MODE_SIZE; /* Destination operand addressing mode */
    unsigned int SRC : ADDRESING_MODE_SIZE; /* Source operand addressing mode */
    unsigned int OPCODE : OPCODE_SIZE;
} FirstWord;

#endif /*ASSEMBLER_WORDS_H */
