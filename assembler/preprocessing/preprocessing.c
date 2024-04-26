/*
 Author: Eitan H.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "preprocessing_context.h"
#include "../../config.h"
#include "macro_table.h"
#include "../utils/utils.h"
#include "preprocessing.h"
#include "../utils/assembly_strings.h"
#include "../../memory_allocator/memory_allocator.h"

static bool check_macro_name(const char* name) { /* Check if the macro name is valid */
    /*
     * The macro name can be anything other than a reserved keyword or a number
     */
    if (check_register(name)) { /* Check if the name is a register */
        return false;
    }
    if (is_operation(name)) { /* Check if the name is an instruction */
        return false;
    }
    if (is_directive(name)) { /* Check if the name is a directive */
        return false;
    }
    if (is_number_signed(name)) { /* Check if the name is a signed number */
        return false;
    }
    return true;
}

static void handle_line(PreprocessingContext* context, char* line);

static void handle_macro_line(PreprocessingContext* context, char* line) {
    const char* macro_name = context->macro_name;
    Macro* macro;
    LineList *macro_lines = context->macro_lines;
    LineNode* current;

    if (strcmp(line, "endmcr") == 0) { /* Check if the line is the end of a macro */
        context->is_macro = false; /* Toggle off the macro flag */
        macro = construct_macro(macro_name);
        macro->lines = macro_lines;
        insert_macro(macro);  /* Insert the macro into the macro table */
        return;
    }
    if (is_macro(line)) { /* Check if the line is a macro */
        macro = find_macro(line); /* Find the macro */
        current = macro->lines->head;
        while (current) { /* Iterate over the lines */
            handle_line(context, current->line); /* Handle the line */
            current = current->next;
        }
        return;
    }
    add_line(macro_lines, line); /* Add the line to the macro lines */
}

static void handle_regular_line(PreprocessingContext* context, char* line) {
    Macro* macro;
    LineNode* current;

    if (strncmp(line, "mcr ", 4) == 0) { /* Check if the line is a macro definition */
        context->macro_lines = construct_line_list();
        context->is_macro = true; /* Toggle on the macro flag */
        context->macro_name = get_operands(line); /* Get the macro name */
        if (!check_macro_name(context->macro_name)) { /* Check if the macro name is valid */
            fprintf(stderr, "Invalid macro name: %s\n", context->macro_name); /* Print an error message */
            free_all_memory(); /* Free all memory */
            exit(EXIT_FAILURE); /* Exit with failure */
        }
        return;
    }
    if (is_macro(line)) { /* Check if the line is a macro */
        macro = find_macro(line); /* Find the macro */
        current = macro->lines->head;
        while (current) { /* Iterate over the lines */
            handle_line(context, current->line); /* Handle the line */
            current = current->next;
        }
        return;
    }
    fprintf(context->output, "%s\n", line); /* write the line to the output */
    fflush(context->output); /* Flush the output buffer */
}

static void handle_line(PreprocessingContext* context, char* line) {
    /* Handle a line of assembly */
    trim_whitespace(line); /* Trim the whitespace from the line */
    if (line[0] == '\0') { /* Check if the line is empty */
        return;
    }
    if (line[0] == ';') { /* Check if the line is a comment */
        return;
    }
    if (context->is_macro) { /* Check if the line is a macro */
        handle_macro_line(context, line);
        return;
    }
    else {
        handle_regular_line(context, line); /* Handle a regular line */
        return;
    }
}

void preprocess(const char* filepath) {
    /* Preprocess the assembly file */
    FILE* input;
    FILE* output;
    PreprocessingContext context;
    const char* preprocessed_filepath;
    char* line;

    init_memory(); /* Initialize the memory allocator */
    init_operation_table();
    init_directive_table();
    line = malloc_track(MAX_LINE_LENGTH); /* Allocate memory for the line */
    init_macro_table(); /* Initialize the macro table */
    input = fopen(filepath, "r");
    if (!input) { /* Check if the file was opened successfully */
        fprintf(stderr, "Failed to open file %s\n", filepath); /* Print an error message */
        free_all_memory(); /* Free all memory */
        exit(EXIT_FAILURE); /* Exit with failure */
    }
    preprocessed_filepath = get_preprocessed_filepath(filepath); /* Get the file path for the preprocessed assembly */
    output = fopen(preprocessed_filepath, "w");
    if (!output) { /* Check if the file was opened successfully */
        fprintf(stderr, "Failed to open file %s\n", preprocessed_filepath); /* Print an error message */
        fclose(input); /* Close the input file */
        free_all_memory();  /* Free all memory */
        exit(EXIT_FAILURE); /* Exit with failure */
    }
    context.is_macro = false;
    context.output = output;

    /* handle line by line */
    while (fgets(line, MAX_LINE_LENGTH, input)) { /* Read line by line from the source assembly */
        handle_line(&context, line); /* Handle the line */
    }

    free_all_memory(); /* Free all memory */
    fclose(input); /* Close the input file */
    fclose(output); /* Close the output file */
}
