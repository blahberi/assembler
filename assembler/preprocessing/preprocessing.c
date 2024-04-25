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
#include "preprocess.h"
#include "../utils/assembly_strings.h"
#include "../../memory_allocator/memory_allocator.h"

static void handle_line(PreprocessingContext* context, char* line);

static void handle_macro_line(PreprocessingContext* context, char* line) {
    const char* macro_name = context->macro_name;
    LineList *macro_lines = context->macro_lines;
    if (strcmp(line, "endmcr") == 0) {
        context->is_macro = false;
        Macro* macro = construct_macro(macro_name);
        macro->lines = macro_lines;
        insert_macro(macro);
        return;
    }
    if (is_macro(line)) {
        Macro* macro = find_macro(line);
        LineNode* current = macro->lines->head;
        while (current) {
            handle_line(context, current->line);
            current = current->next;
        }
        return;
    }
    add_line(macro_lines, line);
}

static void handle_regular_line(PreprocessingContext* context, char* line) {
    if (strncmp(line, "mcr ", 4) == 0) {
        context->macro_lines = construct_line_list();
        context->is_macro = true;
        context->macro_name = get_operands(line);
        context->macro_lines = construct_line_list();
        return;
    }
    if (is_macro(line)) {
        Macro* macro = find_macro(line);
        LineNode* current = macro->lines->head;
        while (current) {
            handle_line(context, current->line);
            current = current->next;
        }
        return;
    }
    fprintf(context->output, "%s\n", line);
    fflush(context->output);
}

static void handle_line(PreprocessingContext* context, char* line) {
    trim_whitespace(line);
    if (line[0] == '\0') {
        return;
    }
    if (line[0] == ';') {
        return;
    }
    if (context->is_macro) {
        handle_macro_line(context, line);
        return;
    }
    else {
        handle_regular_line(context, line);
        return;
    }
}

void preprocess(const char* filepath) {
    init_memory();
    init_macro_table();
    FILE* input = fopen(filepath, "r");
    if (!input) {
        fprintf(stderr, "Failed to open file %s\n", filepath);
        free_all_memory();
        exit(EXIT_FAILURE);
    }
    const char* preprocessed_filepath = get_preprocessed_filepath(filepath);
    FILE* output = fopen(preprocessed_filepath, "w");
    if (!output) {
        fprintf(stderr, "Failed to open file preprocessed.asm\n");
        fclose(input);
        free_all_memory();
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
    free_all_memory();
}