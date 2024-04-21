//
// Author: Eitan H.
//

#ifndef ASSEMBLER_ERRORS_H
#define ASSEMBLER_ERRORS_H

// Define error messages
#define ERR_INVALID_LABEL_NAME "Error: Invalid label name: %s\n"
#define ERR_LABEL_TOO_LONG "Error: Label '%s' is too long\n"

#define ERR_INVALID_IMMEDIATE_VALUE "Error: Invalid immediate value: %s\n"

#define ERR_CONSTANT_TOO_BIG "Error: Constant too big\n"
#define ERR_INVALID_CONSTANT "Error: Invalid constant: %s\n"

#define ERR_LABEL_MUST_BE_MDEFINE "Error: Label '%s' must be mdefine\n"
#define ERR_LABEL_NOT_FOUND "Error: Label '%s' not found\n"
#define ERR_INVALID_DIRECTIVE "Error: Invalid directive: %s\n"
#define ERR_INVALID_OPERATION "Error: Invalid operation: %s\n"
#define ERR_INVALID_REGISTER "Error: Invalid register: %s\n"
#define ERR_INVALID_OPERAND "Error: Invalid operand: %s\n"

#endif //ASSEMBLER_ERRORS_H
