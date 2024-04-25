//
// Author: Eitan H.
//


#include "context/assembler_context.h"
#include "symbol_table/global_symbol_table.h"
#include "extern_handler/extern_handler.h"
#include "words.h"
#include "read_file.h"
#include "utils/utils.h"
#include "context/context.h"
#include "utils/assembly_strings.h"
#include "../memory_tracker/scope_memory_tracker.c.h"
#include "../memory_tracker/global_memory_tracker.h"
#include "preprocessing/preprocess.h"
#include <stdio.h>

void assemble(const char* filename) {
    preprocess(filename);
    filename = "C:\\Users\\blahb\\CLionProjects\\assembler\\preprocessed.asm";

    init_memory_stack();
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

    assembler_context.IC = 0;
    assembler_context.DC = 0;
    assembler_context.is_first_pass = false;

    // Second pass
    read_file(filename, &context);
    symbol_table_update_address(assembler_context.IC);

    if (assembler_context.error) {
        return;
    }
    printf("Instruction Words:\n");
    for (int i = 0; i < assembler_context.IC; i++) {
        print_binary(instruction_words[i].word, 14);
    }
    printf("Data Words:\n");
    for (int i = 0; i < assembler_context.DC; i++) {
        print_binary(data_words[i].word, 14);
    }
    printf("Symbol Table:\n");
    symbol_table_print();

    update_extern_list_address();

    write_extern_file("C:\\Users\\blahb\\CLionProjects\\assembler\\extern.ext");
    write_entry_file("C:\\Users\\blahb\\CLionProjects\\assembler\\entry.ent");

    free_all_memory_stack();
    free_all_global_memory();
}