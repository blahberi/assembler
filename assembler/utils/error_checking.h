//
// Author: Eitan H.
//

#ifndef ASSEMBLER_ERROR_CHECKING_H
#define ASSEMBLER_ERROR_CHECKING_H

#include "../assembler_context.h"

int check_label_err(const char* line, const char* label, const AssemblerContext* context);
#endif //ASSEMBLER_ERROR_CHECKING_H
