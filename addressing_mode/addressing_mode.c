//
// Author: Eitan H. .
//
#include <stdlib.h>
#include "../machine_code_generator/instruction_to_machine_code.h"
#include "../symbol_table/global_symbol_table/global_symbol_table.h"
#include "../utils/utils.h"
#include "../words/operand_words.h"
#include "../machine_code_generator/operand_to_machine_code/operand_to_machine_code.h"


void get_addr_mode(OperandDescriptor* descriptor) {
    const char* operand = descriptor->operand;
    if (operand[0] ==  '#') {
        descriptor->addr_mode = IMMEDIATE;
        descriptor->generate = generate_immediate_operand;
        return;
    }
    if (symbol_table_is_in(operand)) {
        descriptor->addr_mode = DIRECT;
        descriptor->generate = generate_direct_operand;
        return;
    }
    if (strchr(operand, '[') && strchr(operand, ']')) {
        descriptor->addr_mode = INDEX;
        descriptor->generate = generate_index_operand;
        return;
    }
    if (is_register(operand)) {
        descriptor->addr_mode = REGISTER;
        descriptor->generate = generate_register_operand;
        return;
    }
    fprintf(stderr, "Invalid operand: %s\n", operand);
    exit(EXIT_FAILURE); // TODO: Handle error appropriately
}