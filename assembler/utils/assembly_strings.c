/*
 Author: Eitan H.
*/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "utils.h"
#include "../../config.h"
#include "../context/context.h"
#include "../../hash_table/int_hash_table.h"
#include "../../memory_allocator/memory_allocator.h"
#include "../../errors.h"
#include "../symbol_table/global_symbol_table.h"

const char* DEFINE = ".define";

IntHashTable *OPERATION_TABLE;
IntHashTable *DIRECTIVE_TABLE;

void init_operation_table() {
    OPERATION_TABLE = construct_int_hash_table();
    OPERATION_TABLE->insert(OPERATION_TABLE, "mov", MOV);
    OPERATION_TABLE->insert(OPERATION_TABLE, "cmp", CMP);
    OPERATION_TABLE->insert(OPERATION_TABLE, "add", ADD);
    OPERATION_TABLE->insert(OPERATION_TABLE, "sub", SUB);
    OPERATION_TABLE->insert(OPERATION_TABLE, "not", NOT);
    OPERATION_TABLE->insert(OPERATION_TABLE, "clr", CLR);
    OPERATION_TABLE->insert(OPERATION_TABLE, "lea", LEA);
    OPERATION_TABLE->insert(OPERATION_TABLE, "inc", INC);
    OPERATION_TABLE->insert(OPERATION_TABLE, "dec", DEC);
    OPERATION_TABLE->insert(OPERATION_TABLE, "jmp", JMP);
    OPERATION_TABLE->insert(OPERATION_TABLE, "bne", BNE);
    OPERATION_TABLE->insert(OPERATION_TABLE, "red", RED);
    OPERATION_TABLE->insert(OPERATION_TABLE, "prn", PRN);
    OPERATION_TABLE->insert(OPERATION_TABLE, "jsr", JSR);
    OPERATION_TABLE->insert(OPERATION_TABLE, "rts", RTS);
    OPERATION_TABLE->insert(OPERATION_TABLE, "hlt", HLT);
}

void init_directive_table() {
    DIRECTIVE_TABLE = construct_int_hash_table();
    DIRECTIVE_TABLE->insert(DIRECTIVE_TABLE, ".data", DATA_DIRECTIVE);
    DIRECTIVE_TABLE->insert(DIRECTIVE_TABLE, ".string", STRING_DIRECTIVE);
    DIRECTIVE_TABLE->insert(DIRECTIVE_TABLE, ".entry", ENTRY_DIRECTIVE);
    DIRECTIVE_TABLE->insert(DIRECTIVE_TABLE, ".extern", EXTERN_DIRECTIVE);
}

OPCODE find_operation(const char* operation){
    return OPERATION_TABLE->find(OPERATION_TABLE, operation);
}

bool is_operation(const char* operation) {
    return find_operation(operation) != -1;
}

DIRECTIVE_TYPE find_directive(const char* directive){
    return DIRECTIVE_TABLE->find(DIRECTIVE_TABLE, directive);
}

bool is_directive(const char* directive) {
    return find_directive(directive) != -1;
}

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

int get_value_signed(const char* str, int* result) {
    /* this function gets a number or an mdefien label and returns it's int value */
    if (is_number_signed(str)) {
        *result = atoi(str);
        return 0;
    }
    Symbol* symbol = symbol_table_find(str);
    if (symbol == NULL) {
        goto error;
    }
    if (symbol->type != MDEFINE_LABEL) {
        goto error;
    }
    *result = symbol->value;
    return 0;

    error:
    return -1;
}

int get_value_unsigned(const char* str, int* result) {
    if (get_value_signed(str, result) != 0) {
        goto error;
    }
    if (*result < 0) {
        goto error;
    }
    return 0;

    error:
    return -1;
}

char** split_string_by_comma(const char* str) {
    char* str_copy = strdup(str);
    track_pointer(str_copy);
    char** result = malloc_track(sizeof(char *) * (strlen(str) + 1));
    if (!result) {
        fprintf(stderr, ERR_MEMORY_ALLOCATION_FAILED);
        exit(EXIT_FAILURE);
    }
    char* token = strtok(str_copy, ",");
    int i = 0;

    while (token != NULL) {
        result[i] = strdup(token);
        track_pointer(result[i]);
        token = strtok(NULL, ",");
        i++;
    }

    result[i] = NULL; /* Null-terminate the array */
    return result;
}

int comma_seperated_list_length(const char* str) {
    int count = 0;

    /* If the string is not empty, start count from 1 */
    if (str != NULL && *str != '\0') {
        count = 1;
    }

    /* For each character in the string */
    for (const char* c = str; *c != '\0'; c++) {
        /* If the character is a comma, increment the count */
        if (*c == ',') {
            count++;
        }
    }

    return count;
}

void trim_whitespace(char* str) {
    char* start = str;
    char* end = str + strlen(str);

    /* Move start pointer to first non-whitespace character */
    while (isspace((unsigned char)*start)) {
        start++;
    }

    /* Move end pointer to last non-whitespace character */
    while (end > start && isspace((unsigned char)*(end - 1))) {
        end--;
    }

    // Calculate new length
    size_t length = end - start;

    // Shift characters to start of string
    memmove(str, start, length);

    // Null-terminate the string
    str[length] = '\0';
}

bool check_register(const char* operand) {
    // check if starts with r and the rest is a number
    if (operand[0] == 'r' && is_number_unsigned(operand + 1)) {
        int reg_num = atoi(operand + 1);
        if (reg_num < REGISTER_COUNT) { // Check if the register number is valid
            return true;
        }
    }
    return false;
}

bool check_label(const char* label) {
    // Check if label is empty
    if (strlen(label) == 0) {
        return false;
    }

    // Check if label is reserved for register
    if (check_register(label)) {
        return false;
    }

    // Check if label is reserved for instruction
    if (is_operation(label)) {
        return false;
    }

    // Check if label starts with a number
    if (is_number_signed(label)) {
        return false;
    }

    // Check if label exceeds length limit
    if (strlen(label) > MAX_LABEL_LENGTH) {
        return false;
    }

    // Check if all characters are alphanumeric
    for (int i = 0; i < strlen(label); i++) {
        if (!isalnum(label[i])) {
            return false;
        }
    }

    // If none of the above conditions are met, the label is valid
    return true;
}


int parse_index_operand(const char* operand, char* address, char* index) {
    if (strchr(operand, '[') && strchr(operand, ']')) {
        char* operand_copy = strdup(operand);
        track_pointer(operand_copy);
        char* address_str = strtok(operand_copy, "[");
        char* index_str = strtok(NULL, "]");

        if (address_str == NULL || index_str == NULL) {
            return -1;
        }

        strcpy(address, address_str);
        strcpy(index, index_str);
        return 0;
    }
    return -1;
}


bool check_index_operand(const char* operand) {
    char* address = malloc_track(strlen(operand) + 1);
    char* index = malloc_track(strlen(operand) + 1);
    int code = parse_index_operand(operand, address, index);
    if (code != 0) {
        goto error;
    }
    bool address_status = check_label(address);
    bool index_status = check_label(index);

    if (!address_status|| (!index_status && !is_number_unsigned(index))) {
        return false;
    }
    return true;

    error:
    return false;
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
    track_pointer(sentence_copy);
    char* first_word = strtok(sentence_copy, " "); // Get the first word
    char* result = strdup(first_word); // Copy the first word to a new string
    track_pointer(result);
    return result;
}

SENTENCE_TYPE get_sentence_type(const char* sentence) {
    char* sentence_start = get_sentence_start(sentence);

    if (strncmp(sentence_start, DEFINE, strlen(DEFINE)) == 0) {
        return DEFINE_SENTENCE;
    }

    if (is_operation(sentence_start)) {
        return INSTRUCTION_SENTENCE;
    }

    if (is_directive(sentence_start)) {
        return DIRECTIVE_SENTENCE;
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
    track_pointer(operands);
    trim_whitespace(operands);
    return operands;
}

char* get_string_from_quotes(const char* str) {
    if (str[0] == '"' && str[strlen(str) - 1] == '"') {
        char* result = strdup(str + 1);
        track_pointer(result);
        result[strlen(result) - 1] = '\0';
        return result;
    }
    return NULL;
}