//
// Author: Eitan H.
//
#include <stdlib.h>
#include <stdio.h>
#include "instruction_to_machine_code.h"
#include "operand_to_machine_code.h"
#include "utils/assembly_strings.h"
#include "utils/errors.h"

void get_addr_mode(OperandDescriptor *descriptor) {
    const char* operand = descriptor->operand;
    if (operand[0] ==  '#') {
        descriptor->addr_mode = IMMEDIATE;
        descriptor->generate = generate_immediate_operand;
        return;
    }
    if (check_register(operand)){
        descriptor->addr_mode = REGISTER;
        descriptor->generate = generate_register_operand;
        return;
    }
    if (check_label(operand)) {
        descriptor->addr_mode = DIRECT;
        descriptor->generate = generate_direct_operand;
        return;
    }
    if (check_index_operand(operand)) {
        descriptor->addr_mode = INDEX;
        descriptor->generate = generate_index_operand;
        return;
    }
    fprintf(stderr, ERR_INVALID_OPERAND, operand);
    exit(EXIT_FAILURE); // TODO: Handle error appropriately
}