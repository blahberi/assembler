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

void init_operation_table() { /* Initialize the operation table which is used for parsing strings of operations */
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

void init_directive_table() { /* Initialize the directive table which is used for parsing strings of directives */
    DIRECTIVE_TABLE = construct_int_hash_table();
    DIRECTIVE_TABLE->insert(DIRECTIVE_TABLE, ".data", DATA_DIRECTIVE);
    DIRECTIVE_TABLE->insert(DIRECTIVE_TABLE, ".string", STRING_DIRECTIVE);
    DIRECTIVE_TABLE->insert(DIRECTIVE_TABLE, ".entry", ENTRY_DIRECTIVE);
    DIRECTIVE_TABLE->insert(DIRECTIVE_TABLE, ".extern", EXTERN_DIRECTIVE);
}

OPCODE find_operation(const char* operation){ /* Find an operation's opcode given the operation string */
    return OPERATION_TABLE->find(OPERATION_TABLE, operation);
}

bool is_operation(const char* operation) {  /* Check if a string is an operation */
    return find_operation(operation) != -1;
}

DIRECTIVE_TYPE find_directive(const char* directive){ /* Find a directive's type given the directive string */
    return DIRECTIVE_TABLE->find(DIRECTIVE_TABLE, directive);
}

bool is_directive(const char* directive) { /* Check if a string is a directive */
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

bool is_number_signed(const char* str) { /* Check if a string is a signed number */
    if (str == NULL || *str == '\0') {
        return false;
    }

    /* Allow a leading + or - */
    if (*str == '+' || *str == '-') {
        str++; /* Skip the sign */
    }

    return is_number_helper(str);
}

bool is_number_unsigned(const char* str) { /* Check if a string is an unsigned number */
    if (str == NULL || *str == '\0') {
        return false;
    }
    return is_number_helper(str);
}

int get_value_signed(const char* str, int* result) {
    /* this function gets a number or an mdefien label and returns it's int value */
    Symbol* symbol;
    if (is_number_signed(str)) {
        *result = atoi(str);
        return 0;
    }
    symbol = symbol_table_find(str);
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
    /* this function gets a number or an mdefien label and returns it's int value */
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

char** split_string_by_comma(const char* str) { /* Split a string by commas for example "hello,world  , 123,  pizza" will become ["hello", "world", "123", "pizza"] */
    char* str_copy = my_strdup(str);
    char** result = malloc_track(sizeof(char *) * (strlen(str) + 1));
    char* token;
    int i;

    token = strtok(str_copy, ",");
    i = 0;
    while (token != NULL) {
        result[i] = my_strdup(token);
        token = strtok(NULL, ",");
        i++;
    }

    result[i] = NULL; /* Null-terminate the array */
    return result;
}

int comma_seperated_list_length(const char* str) { /* Count the number of elements in a comma-separated list */
    int count = 0;
    const char *c;

    /* If the string is not empty, start count from 1 */
    if (str != NULL && *str != '\0') {
        count = 1;
    }

    /* For each character in the string */
    for (c = str; *c != '\0'; c++) {
        /* If the character is a comma, increment the count */
        if (*c == ',') {
            count++;
        }
    }

    return count;
}

void trim_whitespace(char* str) { /* Remove leading and trailing whitespace from a string */
    char* start = str;
    char* end = str + strlen(str);
    size_t length;

    /* Move start pointer to first non-whitespace character */
    while (isspace((unsigned char)*start)) {
        start++;
    }

    /* Move end pointer to last non-whitespace character */
    while (end > start && isspace((unsigned char)*(end - 1))) {
        end--;
    }

    /* Calculate new length */
    length = end - start;

    /* Shift characters to start of string */
    memmove(str, start, length);

    /* Null-terminate the string */
    str[length] = '\0';
}

bool check_register(const char* operand) { /* Check if a string is a valid register */
    if (operand[0] == 'r' && is_number_unsigned(operand + 1)) { /* Check if the operand starts with 'r' and the rest is a number */
        int reg_num = atoi(operand + 1);
        if (reg_num > 0 && operand[1] == '0') { /* edge case for stuff like "r01" */
            return false;
        }
        if (reg_num < REGISTER_COUNT) { /* Check if the register number is valid */
            return true;
        }
    }
    return false;
}

bool check_label(const char* label) { /* Check if a string is a valid label */
    int i;

    /* Check if label is empty */
    if (strlen(label) == 0) {
        return false;
    }

    /* Check if label is reserved for register */
    if (check_register(label)) {
        return false;
    }

    /* Check if label is reserved for instruction */
    if (is_operation(label)) {
        return false;
    }

    /* Check if label starts with a number */
    if (is_number_signed(label)) {
        return false;
    }

    /* Check if label exceeds length limit */
    if (strlen(label) > MAX_LABEL_LENGTH) {
        return false;
    }

    /* Check if all characters are alphanumeric */
    for (i = 0; i < strlen(label); i++) {
        if (!isalnum(label[i])) {
            return false;
        }
    }

    /* If none of the above conditions are met, the label is valid */
    return true;
}


int parse_index_operand(const char* operand, char* address, char* index) { /* Parse an index operand into an address and an index */
    /*
     * For example, LIST[pizza] will become address = "LIST" and index = "pizza"
     */
    if (strchr(operand, '[') && strchr(operand, ']')) {
        char* operand_copy = my_strdup(operand);
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


bool check_index_operand(const char* operand) { /* Check if a string is a valid index operand */
    char* address = malloc_track(strlen(operand) + 1);
    char* index = malloc_track(strlen(operand) + 1);
    int code = parse_index_operand(operand, address, index);
    bool address_status;
    bool index_status;

    if (code != 0) {
        goto error;
    }
    address_status = check_label(address);
    index_status = check_label(index);

    if (!address_status|| (!index_status && !is_number_unsigned(index))) {
        return false;
    }
    return true;

    error:
    return false;
}


bool is_label_in_line(const char* line) { /* does the line start with "<label>: " */
    char* colon_position = strchr(line, ':');
    if (colon_position != NULL && colon_position != line && *(colon_position - 1) != ' ') {
        return true;
    }
    return false;
}


void split_label_and_sentence(const char* line, char* label, char* sentence) { /* Split a line into a label and a sentence */
    /*
     * For example, "LABEL: MOV r1, r2" will become label = "LABEL" and sentence = "MOV r1, r2"
     */
    char* colon_position = strchr(line, ':');

    /* Copy characters from line to label */
    strncpy(label, line, colon_position - line);
    label[colon_position - line] = '\0'; /* Null-terminate the string */
    trim_whitespace(label);

    /* Copy characters from line to sentence */
    strcpy(sentence, colon_position + 1);
    trim_whitespace(sentence);
}

char* get_sentence_start(const char* sentence) { /* Get the first word of a sentence */
    /*
     * For example, "MOV r1, r2" will return "MOV"
     */
    char* sentence_copy = my_strdup(sentence); /* Create a copy of the sentence to avoid modifying the original string */
    char* first_word = strtok(sentence_copy, " "); /* Get the first word */
    char* result = my_strdup(first_word); /* Copy the first word to a new string */
    return result;
}

SENTENCE_TYPE get_sentence_type(const char* sentence) { /* Get the type of a sentence */
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

    /* If none of the above conditions are met, return an error or a default value */
    return -1;
}

char* get_operands(const char* sentence) { /* Get the operands */
    /*
     * For example, "MOV r1, r2" will return "r1, r2"
     */
    char* space_position = strchr(sentence, ' ');
    char* operands;

    /* If there is no space in the sentence, return NULL */
    if (space_position == NULL) {
        return NULL;
    }

    /* Copy characters from sentence to operands, starting from the character after the space */
    operands = my_strdup(space_position + 1);
    trim_whitespace(operands);
    return operands;
}

char* get_string_from_quotes(const char* str) { /* Get a string from quotes */
    if (str[0] == '"' && str[strlen(str) - 1] == '"') {
        char* result = my_strdup(str + 1);
        result[strlen(result) - 1] = '\0';
        return result;
    }
    return NULL;
}