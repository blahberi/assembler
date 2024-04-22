//
// Author: Eitan H.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../assembler/assembly_strings.h"
#include "../assembler/handle_line.h"
#include "../utils/utils.h"
#include "../symbol_table/global_symbol_table.h"

void test3(){
    create_global_symbol_table();
    char* line = "LOOP: .string \"abcdef\"";

    AssemblerContext context = {
            .is_first_pass = true,
            .IC = 0,
            .DC = 0
    };
    Word *instruction_words = malloc(256 * sizeof(Word));
    Word *data_words = malloc(256 * sizeof(Word));
    memset(instruction_words, 0, 256 * sizeof(Word));
    memset(data_words, 0, 256 * sizeof(Word));
    handle_line(line, &context, instruction_words, data_words);

    for (int i = 0; i < context.IC; i++) {
        print_binary(instruction_words[i].word, 14);
    }
    for (int i = 0; i < context.DC; i++) {
        print_binary(data_words[i].word, 14);
    }

    context.is_first_pass = false;
    context.IC = 0;
    context.DC = 0;

    handle_line(line, &context, instruction_words, data_words);

    printf("\n");

    for (int i = 0; i < context.IC; i++) {
        print_binary(instruction_words[i].word, 14);
    }
    for (int i = 0; i < context.DC; i++) {
        print_binary(data_words[i].word, 14);
    }

    destroy_global_symbol_table();
}