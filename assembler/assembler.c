//
// Author: Eitan H.
//


#include "assembler_context.h"
#include "symbol_table/global_symbol_table.h"
#include "extern_handler/extern_handler.h"
#include "words.h"
#include "read_file.h"
#include "utils/utils.h"

#include <stdlib.h>
#include <stdio.h>

void assemble(const char* filename) {
    AssemblerContext context = {
            .is_first_pass = true,
            .IC = 0,
            .DC = 0,
            .error = false
    };

    create_global_symbol_table();
    init_extern_list();

    Word *instruction_words = calloc(MEMORY_SIZE, sizeof(Word));
    Word *data_words = calloc(MEMORY_SIZE, sizeof(Word));
    // First pass
    read_file(filename, &context, instruction_words, data_words);

    context.IC = 0;
    context.DC = 0;
    context.is_first_pass = false;

    // Second pass
    read_file(filename, &context, instruction_words, data_words);
    symbol_table_update_address(context.IC);

    if (context.error) {
        destroy_global_symbol_table();
        free(instruction_words);
        free(data_words);
        return;
    }
    printf("Instruction Words:\n");
    for (int i = 0; i < context.IC; i++) {
        print_binary(instruction_words[i].word, 14);
    }
    printf("Data Words:\n");
    for (int i = 0; i < context.DC; i++) {
        print_binary(data_words[i].word, 14);
    }
    printf("Symbol Table:\n");
    symbol_table_print();

    update_extern_list_address();

    write_extern_file("C:\\Users\\blahb\\CLionProjects\\assembler\\extern.ext");
    write_entry_file("C:\\Users\\blahb\\CLionProjects\\assembler\\entry.ent");

    free(instruction_words);
    free(data_words);

    destroy_global_symbol_table();
}