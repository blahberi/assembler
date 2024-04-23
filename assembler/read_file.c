//
// Author: Eitan H.
//


#include <stdio.h>
#include <stdlib.h>
#include "../config.h"
#include "handlers/handle_line.h"

int read_file(const char* filename, AssemblerContext* context, Word* instruction_words, Word* data_words) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        int result = handle_line(line, context, instruction_words, data_words);
        if (result == -1) {
            context->error = true;
        }
    }

    fclose(file);
}