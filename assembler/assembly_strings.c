//
// Author: Eitan H.
//

#include <string.h>
#include <stdlib.h>

#include "assembly_strings.h"
#include "../utils/utils.h"
#include "../config.h"
#include "directive_descriptor.h"

const char* INSTRUCTIONS[] = {
        "mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "hlt"
};

const char* DIRECTIVES[] = {
        ".data", ".string", ".entry", ".extern"
};

const char* DEFINE = ".define";


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


bool is_label_in_line(const char* line) { // does the line start with "<label>: "
    char* colon_position = strchr(line, ':');
    if (colon_position != NULL && colon_position != line && *(colon_position - 1) != ' ') {
        return true;
    }
    return false;
}


void split_label_and_sentence(const char* line, char* label, char* sentence) {
    char* colon_position = strchr(line, ':');

    // Copy characters from line to label
    strncpy(label, line, colon_position - line);
    label[colon_position - line] = '\0'; // Null-terminate the string
    trim_whitespace(label);

    // Copy characters from line to sentence
    strcpy(sentence, colon_position + 1);
    trim_whitespace(sentence);
}

char* get_sentence_start(const char* sentence) {
    char* sentence_copy = strdup(sentence); // Create a copy of the sentence to avoid modifying the original string
    char* first_word = strtok(sentence_copy, " "); // Get the first word
    char* result = strdup(first_word); // Copy the first word to a new string
    free(sentence_copy);
    return result;
}

SENTENCE_TYPE get_sentence_type(const char* sentence) {
    if (strncmp(sentence, DEFINE, strlen(DEFINE)) == 0) {
        return DEFINE_SENTENCE;
    }

    for (int i = 0; i < sizeof(DIRECTIVES) / sizeof(DIRECTIVES[0]); i++) {
        if (strncmp(sentence, DIRECTIVES[i], strlen(DIRECTIVES[i])) == 0) {
            return DIRECTIVE_SENTENCE;
        }
    }

    for (int i = 0; i < sizeof(INSTRUCTIONS) / sizeof(INSTRUCTIONS[0]); i++) {
        if (strncmp(sentence, INSTRUCTIONS[i], strlen(INSTRUCTIONS[i])) == 0) {
            return INSTRUCTION_SENTENCE;
        }
    }

    // If none of the above conditions are met, return an error or a default value
    return -1;
}

char* get_operands(const char* sentence) {
    char* space_position = strchr(sentence, ' ');

    // If there is no space in the sentence, return NULL
    if (space_position == NULL) {
        return NULL;
    }

    // Copy characters from sentence to operands, starting from the character after the space
    char* operands = strdup(space_position + 1);
    trim_whitespace(operands);
    return operands;
}