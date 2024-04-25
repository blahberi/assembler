/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_ASSEMBLY_STRINGS_H
#define ASSEMBLER_ASSEMBLY_STRINGS_H


#include "../sentence_type.h"
#include "../descriptors/operation_descriptor.h"

typedef struct context Context;

void init_operation_table();
void init_directive_table();
OPCODE find_operation(const char* operation);
bool is_operation(const char* str);
bool is_directive(const char* str);
bool is_number_signed(const char* str);
bool is_number_unsigned(const char* str);
int get_value_signed(const char* str, int* result);
int get_value_unsigned(const char* str, int* result);
char** split_string_by_comma(const char* str);
int comma_seperated_list_length(const char* str);
void trim_whitespace(char* str);
bool check_register(const char* operand);
bool check_label(const char* label);
int parse_index_operand(const char* operand, char* address, char* index);
bool check_index_operand(const char* operand);
bool is_label_in_line(const char* line);
void split_label_and_sentence(const char* line, char* label, char* sentence);
char* get_sentence_start(const char* sentence);
SENTENCE_TYPE get_sentence_type(const char* sentence);
char* get_operands(const char* sentence);
char* get_string_from_quotes(const char* str);


#endif /* ASSEMBLER_ASSEMBLY_STRINGS_H */
