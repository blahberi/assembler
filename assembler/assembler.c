/*
 Author: Eitan H.
*/


#include "context/assembler_context.h"
#include "symbol_table/global_symbol_table.h"
#include "extern_handler/extern_handler.h"
#include "words.h"
#include "read_file.h"
#include "context/context.h"
#include "utils/assembly_strings.h"
#include "preprocessing/preprocessing.h"
#include "../memory_allocator/memory_allocator.h"
#include "write_file.h"
#include "utils/utils.h"
#include "../errors.h"
#include <stdio.h>
#include <stdlib.h>


void assemble(const char* filepath) {
    /* Assemble the assembly file */

    int i;
    const char* preprocessed_filepath;
    AssemblerContext assembler_context;
    Context context;
    Word* instruction_words;
    Word* data_words;
    Word* output_words;
    int ic;
    int dc;
    const char* output_filepath;
    const char* extern_filepath;
    const char* entry_filepath;

    preprocess(filepath); /* Preprocess the assembly */
    init_memory(); /* Initialize the memory allocator */
    preprocessed_filepath = get_preprocessed_filepath(filepath); /* Get the file path for the preprococessed assembly */
    assembler_context.IC = 0;
    assembler_context.DC = 0;
    assembler_context.error = false;
    assembler_context.is_first_pass = true;

    init_global_symbol_table(); /* Initialize the global symbol table */
    init_extern_list(); /* Initialize the extern list */
    init_operation_table(); /* For string parsing */
    init_directive_table(); /* For string parsing */

    instruction_words = calloc_track(MEMORY_SIZE, sizeof(Word)); /* Allocate memory for the instruction words */
    data_words = calloc_track(MEMORY_SIZE, sizeof(Word)); /* Allocate memory for the data words */

    context.assembler_context = &assembler_context;
    context.instruction_words = instruction_words;
    context.data_words = data_words;

    context.line_descriptor = malloc_track(sizeof(LineDescriptor));
    context.instruction = malloc_track(sizeof(InstructionLineDescriptor));

    /* First pass */
    read_file(preprocessed_filepath, &context);
    symbol_table_update_address(assembler_context.IC); /* Add the IC to the addresses of the symbols */

    assembler_context.IC = 0;
    assembler_context.DC = 0;
    assembler_context.is_first_pass = false;

    /* Second pass */
    read_file(preprocessed_filepath, &context);
    if (assembler_context.error) { /* If there was an error during the second pass */
        free_all_memory(); /* Free all memory */
        exit(EXIT_FAILURE); /* Exit with failure */
    }

    output_words = calloc_track(MEMORY_SIZE - 100, sizeof(Word)); /* Allocate memory for the output words */
    ic = assembler_context.IC;
    dc = assembler_context.DC;
    if (ic + dc > MEMORY_SIZE - 100) { /* Assembly file is too large */
        fprintf(stderr, ERR_MEMORY_OVERFLOW); /* Print an error message */
        free_all_memory(); /* Free all memory */
        exit(EXIT_FAILURE); /* Exit with failure */
    }
    for (i = 0; i < ic; i++) {
        output_words[i] = instruction_words[i]; /* Copy the instruction words to the output words */
    }
    for (i = 0; i < dc; i++) {
        output_words[ic + i] = data_words[i]; /* Copy the data words to the output words */
    }

    output_filepath = get_output_filename(filepath); /* Get the output file path */

    write_file(output_filepath, output_words, ic, dc); /* Write the output words to the output file */

    update_extern_list_address(); /* Update the addresses of the externs */

    extern_filepath = get_extern_filename(filepath); /* Get the extern file path */
    entry_filepath = get_entry_filename(filepath); /* Get the entry file path */
    write_extern_file(extern_filepath); /* Write the extern file */
    write_entry_file(entry_filepath); /* Write the entry file */

    free_all_memory();

    printf("Assembling completed successfully\n");
}
