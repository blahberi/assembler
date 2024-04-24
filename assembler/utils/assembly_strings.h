//
// Author: Eitan H.
//

#ifndef ASSEMBLER_ASSEMBLY_STRINGS_H
#define ASSEMBLER_ASSEMBLY_STRINGS_H

#include <stdbool.h>
#include "../sentence_type.h"

typedef struct context Context;

extern const char* INSTRUCTIONS[];
extern const char* DIRECTIVES[];
const char* DEFINE;


bool is_instruction(const char* str);
bool check_register(const char* operand);
bool check_label(const char* label);
int parse_index_operand(const char* operand, char* address, char* index);
bool check_index_operand(const char* operand);
bool is_label_in_line(const char* line);
void split_label_and_sentence(const char* line, char* label, char* sentence);
char* get_sentence_start(const char* sentence);
SENTENCE_TYPE get_sentence_type(const char* sentence);
char* get_operands(Context* context);

#endif //ASSEMBLER_ASSEMBLY_STRINGS_H
