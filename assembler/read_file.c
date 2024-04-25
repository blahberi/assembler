//
// Author: Eitan H.
//


#include <stdio.h>
#include <stdlib.h>
#include "../config.h"
#include "handlers/handle_line.h"
#include "context/context.h"
#include "../memory_tracker/scope_memory_tracker.c.h"

int read_file(const char* filename, Context* context) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        increment_memory_stack();
        context->line_descriptor->line = line;
        int result = handle_line(context);
        if (result == -1) {
            context->assembler_context->error = true;
        }
        pop_memory_stack();
    }

    fclose(file);
    if (context->assembler_context->error) {
        return -1;
    }
    return 0;
}