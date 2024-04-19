#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "assembler/instruction_to_machine_code.h"
#include "symbol_table/global_symbol_table.h"

int main() {
    create_global_symbol_table();
    symbol_table_insert(construct_symbol("sz", 2, false));
    symbol_table_insert(construct_symbol("MAIN", 100, false));
    symbol_table_insert(construct_symbol("LOOP", 104, false));
    symbol_table_insert(construct_symbol("L1", 120, false));
    symbol_table_insert(construct_symbol("END", 124, false));
    symbol_table_insert(construct_symbol("len", 4, false));
    symbol_table_insert(construct_symbol("STR", 125, false));
    symbol_table_insert(construct_symbol("LIST", 132, false));
    symbol_table_insert(construct_symbol("K", 135, false));

    OperationDescriptor op_desc = {
        .opcode = MOV,
        .generate = generate_two_word_instruction
    };
    OperandDescriptor src_desc = {
        .operand = "r3",
        .addr_mode = REGISTER,
        .is_dest = false,
        .generate = NULL
    };
    OperandDescriptor dest_desc = {
        .operand = "LIST[sz]",
        .is_dest = true,
        .generate = NULL
    };

    OperandDescriptor operands[2] = {src_desc, dest_desc};

    InstructionWord instruction_words[5];
    memset(instruction_words, 0, sizeof(instruction_words));


    int len = op_desc.generate(&op_desc, operands, instruction_words);

    // print the instruction words in binary with 1 line per word
    for (int i = 0; i < len; i++) {
        for (int j = 13; j >= 0; j--) {
            printf("%d", (instruction_words[i].word >> j) & 1);
        }
        printf("\n");
    }

    return 0;
}
