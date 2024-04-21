//
// Author: Eitan H.
//

#ifndef ASSEMBLER_HANDLE_LABEL_H
#define ASSEMBLER_HANDLE_LABEL_H

#include "assembler_context.h"

void check_label_and_error(const char* label);
void find_label_and_error(const char* label);
int handle_label_instruction(const char* label, const AssemblerContext* context);
int handle_label_data(const char* label, const AssemblerContext* context);
int handle_label_extern(const char* label, const AssemblerContext* context);

#endif //ASSEMBLER_HANDLE_LABEL_H
