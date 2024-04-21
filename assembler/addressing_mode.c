//
// Author: Eitan H.
//
#include <stdlib.h>
#include <string.h>
#include "instruction_to_machine_code.h"
#include "operand_to_machine_code.h"
#include "assembly_strings.h"
#include "../errors.h"

void get_addr_mode(OperandDescriptor *descriptor, const AssemblerContext *context) {
    const char* operand = descriptor->operand;
    if (operand[0] ==  '#') {
        descriptor->addr_mode = IMMEDIATE;
        descriptor->generate = generate_immediate_operand;
        return;
    }
    if (check_register(operand) == VALID_REGISTER){
        descriptor->addr_mode = REGISTER;
        descriptor->generate = generate_register_operand;
        return;
    }
    if (check_label(operand)) {
        descriptor->addr_mode = DIRECT;
        descriptor->generate = generate_direct_operand;
        return;
    }
    if (check_index_operand(operand) == VALID_OPERAND) {
        descriptor->addr_mode = INDEX;
        descriptor->generate = generate_index_operand;
        return;
    }
    fprintf(stderr, ERR_INVALID_OPERAND, operand);
    exit(EXIT_FAILURE); // TODO: Handle error appropriately
}