//
// Author: Eitan H.
//


#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "utils.h"

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