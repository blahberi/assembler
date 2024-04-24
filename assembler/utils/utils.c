//
// Author: Eitan H.
//


#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "utils.h"
#include "../symbol_table/global_symbol_table.h"

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
    // this function gets a number or an mdefien label and returns it's int value
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

void print_binary(unsigned int num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

char** split_string_by_comma(const char* str) {
    char* str_copy = strdup(str);
    char** result = malloc(sizeof(char*) * (strlen(str) + 1)); // Allocate enough pointers
    char* token = strtok(str_copy, ",");
    int i = 0;

    while (token != NULL) {
        result[i] = strdup(token);
        token = strtok(NULL, ",");
        i++;
    }

    result[i] = NULL; // Null-terminate the array
    free(str_copy);
    return result;
}

int comma_seperated_list_length(const char* str) {
    int count = 0;

    // If the string is not empty, start count from 1
    if (str != NULL && *str != '\0') {
        count = 1;
    }

    // For each character in the string
    for (const char* c = str; *c != '\0'; c++) {
        // If the character is a comma, increment the count
        if (*c == ',') {
            count++;
        }
    }

    return count;
}

void trim_whitespace(char* str) {
    char* start = str;
    char* end = str + strlen(str);

    // Move start pointer to first non-whitespace character
    while (isspace((unsigned char)*start)) {
        start++;
    }

    // Move end pointer to last non-whitespace character
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