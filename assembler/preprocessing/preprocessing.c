//
// Author: Eitan H.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "preprocessing_context.h"
#include "../../config.h"
#include "macro_table.h"
#include "../utils/utils.h"
#include "../../memory_tracker/global_memory_tracker.h"
#include "preprocess.h"
#include "../utils/assembly_strings.h"
#include "../../memory_tracker/scope_memory_tracker.c.h"

static int handle_line(PreprocessingContext* context, char* line);

static int handle_macro_line(PreprocessingContext* context, char* line) {
    const char* macro_name = context->macro_name;
    LineList *macro_lines = context->macro_lines;
    if (strcmp(line, "endmcr") == 0) {
        context->is_macro = false;
        Macro* macro = construct_macro(macro_name);
        macro->lines = macro_lines;
        insert_macro(macro);
        return 0;
    }
    if (is_macro(line)) {
        Macro* macro = find_macro(line);
        LineNode* current = macro->lines->head;
        while (current) {
            handle_line(context, current->line);
            current = current->next;
        }
        return 0;
    }
    add_line(macro_lines, line);
    return 0;
}

static int handle_regular_line(PreprocessingContext* context, char* line) {
    if (strncmp(line, "mcr ", 4) == 0) {
        context->macro_lines = construct_line_list();
        context->is_macro = true;
        context->macro_name = get_operands(line);
        context->macro_lines = construct_line_list();
        return 0;
    }
    if (is_macro(line)) {
        Macro* macro = find_macro(line);
        LineNode* current = macro->lines->head;
        while (current) {
            handle_line(context, current->line);
            current = current->next;
        }
        return 0;
    }
    fprintf(context->output, "%s\n", line);
    fflush(context->output);
    return 0;
}

static int handle_line(PreprocessingContext* context, char* line) {
    trim_whitespace(line);
    if (line[0] == '\0') {
        return 0;
    }
    if (line[0] == ';') {
        return 0;
    }
    if (context->is_macro) {
        return handle_macro_line(context, line);
    }
    else {
        return handle_regular_line(context, line);
    }
}

int preprocess(const char* filename) {
    init_macro_table();
    init_memory_stack();
    FILE* input = fopen(filename, "r");
    if (!input) {
        fprintf(stderr, "Failed to open file %s\n", filename);
        free_all_global_memory();
        exit(EXIT_FAILURE);
    }
    FILE* output = fopen("C:\\Users\\blahb\\CLionProjects\\assembler\\preprocessed.asm", "w");
    if (!output) {
        fprintf(stderr, "Failed to open file preprocessed.asm\n");
        fclose(input);
        free_all_global_memory();
        exit(EXIT_FAILURE);
    }
    PreprocessingContext context = {
        .is_macro = false,
        .macro_name = NULL,
        .output = output
    };

    // handle line by line
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input)) {
        handle_line(&context, line);
    }
    free_all_global_memory();
    free_all_memory_stack();
    return 0;
}