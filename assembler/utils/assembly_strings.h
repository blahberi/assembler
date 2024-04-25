/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_ASSEMBLY_STRINGS_H
#define ASSEMBLER_ASSEMBLY_STRINGS_H


#include "../descriptors/operation_descriptor.h"

void init_operation_table(); /* Hash table for string parsing */
void init_directive_table(); /* Hash table for string parsing */
OPCODE find_operation(const char* operation); /* Get the OPCODE given an operation string */
bool is_operation(const char* str); /* Check if a string is an operation */
bool is_directive(const char* str); /* Check if a string is a directive */
bool is_number_signed(const char* str); /* Check if a string is a signed number */
bool is_number_unsigned(const char* str); /* Check if a string is an unsigned number */
int get_value_signed(const char* str, int* result); /* Get the signed value of a string, even if that string is a mdefine symbol */
int get_value_unsigned(const char* str, int* result); /* Get the unsigned value of a string, even if that string is a mdefine symbol */
char** split_string_by_comma(const char* str); /* Split a string by commas */
int comma_seperated_list_length(const char* str); /* Get the length of a comma seperated list */
void trim_whitespace(char* str); /* Remove leading and trailing whitespace from a string */
bool check_register(const char* operand); /* Check if a string is a register */
bool check_label(const char* label); /* Check if a string is a valid label (does not check it in the symbol table, just checks if it follows the rule for symbols) */
int parse_index_operand(const char* operand, char* address, char* index); /* Parse an index operand */
bool check_index_operand(const char* operand); /* Check if a string is an index operand */
bool is_label_in_line(const char* line); /* Check if a line starts with "<label>: " */
void split_label_and_sentence(const char* line, char* label, char* sentence); /* Split a line into a label and a sentence */
char* get_sentence_start(const char* sentence); /* Get the first word of a sentence */
SENTENCE_TYPE get_sentence_type(const char* sentence); /* Get the type of a sentence */
char* get_operands(const char* sentence); /* Get the operands of a sentence */
char* get_string_from_quotes(const char* str); /* Get the string between quotes */


#endif /* ASSEMBLER_ASSEMBLY_STRINGS_H */
