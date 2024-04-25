/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_PREPROCESSING_CONTEXT_H
#define ASSEMBLER_PREPROCESSING_CONTEXT_H

#include <stdbool.h>
#include <stdio.h>
#include "line_list.h"

typedef struct PreprocessingContext {
    bool is_macro;
    char* macro_name;
    LineList* macro_lines;
    FILE* output;
} PreprocessingContext;

#endif /* ASSEMBLER_PREPROCESSING_CONTEXT_H */
