/*
 Author: Eitan H.
*/


#include <stdio.h>
#include <stdlib.h>
#include "context/context.h"
#include "../memory_allocator/memory_allocator.h"
#include "handlers/handle_line.h"

int read_file(const char* filepath, Context* context) { /* Read the file and handle each line */
    int result;
    char line[MAX_LINE_LENGTH];
    FILE* file = fopen(filepath, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filepath);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) { /* Read each line */
        push_memory();
        context->line_descriptor->line = line; /* populate the context */
        result = handle_line(context); /* Handle the line */
        if (result == -1) { /* If there was an error */
            context->assembler_context->error = true; /* Set the error flag */
        }
        pop_memory();
    }
    fclose(file);
    if (context->assembler_context->error) {
        return -1; /* If there was an error, return -1 */
    }
    return 0;
}