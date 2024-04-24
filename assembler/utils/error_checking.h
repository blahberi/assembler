//
// Author: Eitan H.
//

#ifndef ASSEMBLER_ERROR_CHECKING_H
#define ASSEMBLER_ERROR_CHECKING_H

#include "../context/assembler_context.h"

typedef struct context Context;

int check_label_err(const char* label, const Context* context);
#endif //ASSEMBLER_ERROR_CHECKING_H
