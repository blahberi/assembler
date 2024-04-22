//
// Author: Eitan H.
//

#include <stdio.h>
#include <stdlib.h>
#include <vcruntime_string.h>
#include "../assembler/handle_line.h"
#include "../assembler/assembler_context.h"
#include "../symbol_table/global_symbol_table.h"
#include "../utils/utils.h"

void read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    create_global_symbol_table();

    AssemblerContext context = {
            .is_first_pass = true,
            .IC = 0,
            .DC = 0
    };

    Word *instruction_words = malloc(MEMORY_SIZE * sizeof(Word));
    Word *data_words = malloc(MEMORY_SIZE * sizeof(Word));

    memset(instruction_words, 0, MEMORY_SIZE * sizeof(Word));
    memset(data_words, 0, MEMORY_SIZE * sizeof(Word));

    char line[MAX_LINE_LENGTH];

    // First pass
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        handle_line(line, &context, instruction_words, data_words);
    }

    symbol_table_update_address(context.IC);

    // Reset file pointer and context for second pass
    fseek(file, 0, SEEK_SET);
    context.is_first_pass = false;
    context.IC = 0;
    context.DC = 0;

    // Second pass
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        handle_line(line, &context, instruction_words, data_words);
    }

    printf("Instruction Words:\n");
    for (int i = 0; i < context.IC; i++) {
        print_binary(instruction_words[i].word, 14);
    }
    printf("Data Words:\n");
    for (int i = 0; i < context.DC; i++) {
        print_binary(data_words[i].word, 14);
    }

    fclose(file);

    free(instruction_words);
    free(data_words);

    printf("Symbol Table:\n");
    symbol_table_print();
    destroy_global_symbol_table();
}