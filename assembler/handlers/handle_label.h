//
// Author: Eitan H.
//

#ifndef ASSEMBLER_HANDLE_LABEL_H
#define ASSEMBLER_HANDLE_LABEL_H

#include "../assembler_context.h"

typedef int LabelHandler(const char* label, const char* line, const AssemblerContext* context);

int handle_label_instruction(const char* label, const char* line, const AssemblerContext* context);
int handle_label_data(const char* label, const char* line, const AssemblerContext* context);
int handle_label_entry(const char* label, const char* line, const AssemblerContext* context);
int handle_label_extern(const char* label, const char* line, const AssemblerContext* context);

#endif //ASSEMBLER_HANDLE_LABEL_H
