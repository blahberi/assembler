//
// Author: Eitan H.
//

#ifndef ASSEMBLER_READ_FILE_H
#define ASSEMBLER_READ_FILE_H

#include "assembler_context.h"
#include "words.h"

void read_file(const char* filename, AssemblerContext* context, Word* instruction_words, Word* data_words);

#endif //ASSEMBLER_READ_FILE_H
