//
// Author: Eitan H.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../assembler/instruction_to_machine_code.h"
#include "../symbol_table/global_symbol_table.h"
#include "../utils/utils.h"

void test1() {
    create_global_symbol_table();
    symbol_table_insert(construct_symbol("sz", MDEFINE_LABEL, 2, false, false));
    symbol_table_insert(construct_symbol("MAIN", CODE_LABEL, 100, false, false));
    symbol_table_insert(construct_symbol("LOOP", CODE_LABEL, 104, false, false));
    symbol_table_insert(construct_symbol("L1", CODE_LABEL, 120, false, false));
    symbol_table_insert(construct_symbol("END", CODE_LABEL, 124, false, false));
    symbol_table_insert(construct_symbol("len", MDEFINE_LABEL, 4, false, false));
    symbol_table_insert(construct_symbol("STR", DATA_LABEL, 125, false, false));
    symbol_table_insert(construct_symbol("LIST", DATA_LABEL, 132, false, false));
    symbol_table_insert(construct_symbol("K", DATA_LABEL, 135, false, false));

    OperationDescriptor op_desc = {
            .opcode = MOV,
            .generate = generate_two_word_instruction
    };
    OperandDescriptor src_desc = {
            .operand = "r3",
    };
    OperandDescriptor dest_desc = {
            .operand = "LIST[sz]",
    };
    Word *instruction_words = malloc(5 * sizeof(Word));
    memset(instruction_words, 0, 5 * sizeof(Word));
    OperandDescriptor operands[2] = {src_desc, dest_desc};

    AssemblerContext context = {
            .IC = 100,
            .is_first_pass = false,
    };
}