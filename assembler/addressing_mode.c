//
// Author: Eitan H. .
//
#include <stdlib.h>
#include <string.h>
#include "instruction_to_machine_code.h"
#include "../symbol_table/global_symbol_table.h"
#include "../utils/utils.h"
#include "operand_to_machine_code.h"


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
    if (is_register(operand) == 0) {
        descriptor->addr_mode = REGISTER;
        descriptor->generate = generate_register_operand;
        return;
    }
    fprintf(stderr, "Invalid operand: %s\n", operand);
    exit(EXIT_FAILURE); // TODO: Handle error appropriately
}