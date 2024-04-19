//
// Author: Eitan H.
//


#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "utils.h"
#include "../config.h"
#include "../assembler/register_error.h"

bool is_number_helper(const char* str){
    while (*str != '\0') {
        if (!isdigit((unsigned char)*str)) {
            return false;
        }
        str++;
    }
    return true;
}

bool is_number_signed(const char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    // Allow a leading + or -
    if (*str == '+' || *str == '-') {
        str++; // Skip the sign
    }

    return is_number_helper(str);
}

bool is_number_unsigned(const char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    return is_number_helper(str);
}

int is_register(const char* operand) {
    // check if starts with r and the rest is a number
    if (operand[0] == 'r' && is_number_unsigned(operand + 1)) {
        int reg_num = atoi(operand + 1);
        if (reg_num < REGISTER_COUNT) { // Check if the register number is valid
            return 0;
        }
        return INVALID_REGISTER_ID;
    }
    return INVALID_REGISTER_NAME;
}