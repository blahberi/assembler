//
// Author: Eitan H.
//


#include "context/assembler_context.h"
#include "symbol_table/global_symbol_table.h"
#include "extern_handler/extern_handler.h"
#include "words.h"
#include "read_file.h"
#include "context/context.h"
#include "utils/assembly_strings.h"
#include "preprocessing/preprocess.h"
#include "../memory_allocator/memory_allocator.h"
#include "write_file.h"
#include <stdio.h>
#include <stdlib.h>

void assemble(const char* filename) {
    preprocess(filename);
    filename = "C:\\Users\\blahb\\CLionProjects\\assembler\\preprocessed.asm";

    init_memory();
    AssemblerContext assembler_context = {
            .is_first_pass = true,
            .IC = 0,
            .DC = 0,
            .error = false
    };

    init_global_symbol_table();
    init_extern_list();
    init_operation_table();
    init_directive_table();

    Word *instruction_words = calloc_track(MEMORY_SIZE, sizeof(Word));
    Word *data_words = calloc_track(MEMORY_SIZE, sizeof(Word));

    Context context = {
            .assembler_context = &assembler_context,
            .line_descriptor = NULL,
            .instruction = NULL,
            .directive = NULL,
            .instruction_words = instruction_words,
            .data_words = data_words,
    };

    context.line_descriptor = malloc_track(sizeof(LineDescriptor));
    context.instruction = malloc_track(sizeof(InstructionLineDescriptor));

    // First pass
    read_file(filename, &context);
    symbol_table_update_address(assembler_context.IC);

    assembler_context.IC = 0;
    assembler_context.DC = 0;
    assembler_context.is_first_pass = false;

    // Second pass
    read_file(filename, &context);
    if (assembler_context.error) {
        free_all_memory();
        exit(EXIT_FAILURE);
    }

    Word *output_words = calloc_track(MEMORY_SIZE - 100, sizeof(Word));
    int ic = assembler_context.IC;
    int dc = assembler_context.DC;
    for (int i = 0; i < ic; i++) {
        output_words[i] = instruction_words[i];
    }
    for (int i = 0; i < dc; i++) {
        output_words[ic + i] = data_words[i];
    }

    symbol_table_print();

    write_file("C:\\Users\\blahb\\CLionProjects\\assembler\\output.obj", output_words, ic, dc);

    update_extern_list_address();

    write_extern_file("C:\\Users\\blahb\\CLionProjects\\assembler\\extern.ext");
    write_entry_file("C:\\Users\\blahb\\CLionProjects\\assembler\\entry.ent");

    free_all_memory();
}