//
// Author: Eitan H.
//

#include <string.h>
#include <stdlib.h>

#include "assembly_strings.h"
#include "../utils/utils.h"
#include "../config.h"


REGISTER_STATUS check_register(const char* operand) {
    // check if starts with r and the rest is a number
    if (operand[0] == 'r' && is_number_unsigned(operand + 1)) {
        int reg_num = atoi(operand + 1);
        if (reg_num < REGISTER_COUNT) { // Check if the register number is valid
            return VALID_REGISTER;
        }
        return INVALID_REGISTER_ID;
    }
    return INVALID_REGISTER_NAME;
}

// List of all instruction names
const char* INSTRUCTIONS[] = {
        "MOV", "ADD", "SUB", "AND", "OR", "NOT", "JMP", "JZ", "JNZ", "JGT", "CALL", "RET", "PUSH", "POP", "HLT"
};
const int INSTRUCTION_COUNT = sizeof(INSTRUCTIONS) / sizeof(INSTRUCTIONS[0]);

bool is_instruction(const char* str) {
    for (int i = 0; i < INSTRUCTION_COUNT; i++) {
        if (strcmp(str, INSTRUCTIONS[i]) == 0) {
            return true;
        }
    }
    return false;
}


LABEL_STATUS check_label(const char* label) {
    // Check if label is empty
    if (strlen(label) == 0) {
        return INVALID_LABEL;
    }

    // Check if label is reserved for register
    if (check_register(label) == VALID_REGISTER) {
        return INVALID_LABEL;
    }

    // Check if label is reserved for instruction
    if (is_instruction(label)) {
        return INVALID_LABEL;
    }

    // Check if label starts with a number
    if (is_number_signed(label)) {
        return INVALID_LABEL;
    }

    // Check if label exceeds length limit
    if (strlen(label) > MAX_LABEL_LENGTH) {
        return INVALID_LABEL_LENGTH;
    }

    // Check if all characters are alphanumeric
    for (int i = 0; i < strlen(label); i++) {
        if (!isalnum(label[i])) {
            return INVALID_LABEL;
        }
    }

    // If none of the above conditions are met, the label is valid
    return VALID_LABEL;
}


int parse_index_operand(const char* operand, char* address, char* index) {
    if (strchr(operand, '[') && strchr(operand, ']')) {
        char* operand_copy = strdup(operand);
        char* address_str = strtok(operand_copy, "[");
        char* index_str = strtok(NULL, "]");

        strcpy(address, address_str);
        strcpy(index, index_str);

        free(operand_copy);
        return 0;
    }
    return -1;
}

INDEX_OPERAND_STATUS check_index_operand(const char* operand) {
    char* address = malloc(strlen(operand) + 1);
    char* index = malloc(strlen(operand) + 1);
    int code = parse_index_operand(operand, address, index);
    if (code == -1) {
        free(address);
        free(index);
        return INVALID_OPERAND;
    }
    LABEL_STATUS address_status = check_label(address);
    LABEL_STATUS index_status = check_label(index);

    if (address_status!= VALID_LABEL) {
        free(address);
        free(index);
        switch(address_status) {
            case INVALID_LABEL:
                return INVALID_OPERAND_LABEL;
            case INVALID_LABEL_LENGTH:
                return INVALID_OPERAND_LABEL_LENGTH;
        }
    }
    if (index_status != VALID_LABEL && !is_number_unsigned(index)) {
        free(address);
        free(index);
        switch(index_status) {
            case INVALID_LABEL:
                return INVALID_OPERAND_INDEX;
            case INVALID_LABEL_LENGTH:
                return INVALID_OPERAND_INDEX_LENGTH;
        }
    }
    free(address);
    free(index);
    return VALID_OPERAND;
}