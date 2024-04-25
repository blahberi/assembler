/*
 Author: Eitan H.
*/


#include <stdio.h>
#include <stdlib.h>
#include "context/context.h"
#include "../memory_allocator/memory_allocator.h"
#include "handlers/handle_line.h"

int read_file(const char* filepath, Context* context) {
    int result;
    char line[MAX_LINE_LENGTH];
    FILE* file = fopen(filepath, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filepath);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        push_memory();
        context->line_descriptor->line = line;
        result = handle_line(context);
        if (result == -1) {
            context->assembler_context->error = true;
        }
        pop_memory();
    }

    fclose(file);
    if (context->assembler_context->error) {
        return -1;
    }
    return 0;
}