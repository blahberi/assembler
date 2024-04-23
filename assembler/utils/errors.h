//
// Author: Eitan H.
//

#ifndef ASSEMBLER_ERRORS_H
#define ASSEMBLER_ERRORS_H

#define ERR_INVALID_SENTENCE "Error: Invalid sentence:\n %s\n"
#define ERR_MISSING_COMMA "Error: Missing comma:\n %s\n"
#define ERR_EMPTY_OPERAND "Error: Empty operand:\n %s\n"
#define ERR_LABEL_TOO_LONG "Error: Label '%s' too long, max 31 characters:\n %s\n"
#define ERR_DEFINE_GOT_LABEL "Error: .define does not expect a label\n %s\n"
#define ERR_DEFINE_DIDNT_GET_VALUE "Error: .define expects operand <symbol>=<value>\n %s\n"
#define ERR_INVALID_DEFINE_VALUE "Error: .define value must be a number or an mdefine symbol\n %s\n"
#define ERR_INVALID_DATA_OPERAND "Error: .data operand must be a number or an mdefine symbol\n %s\n"
#define ERR_DATA_EXPECTS_OPERANDS "Error: .data expects at least one operand\n %s\n"
#define ERR_IMMEDIATE_MUST_BE_NUMBER "Error: Immediate operand must be a number or an mdefine symbol\n %s\n"
#define ERR_INDEX_MUST_BE_NUMBER "Error: Index must be a number or an mdefine symbol\n %s\n"
#define ERR_INVALID_OPERAND "Error: Invalid operand\n %s\n"
#define ERR_LABEL_ALREADY_EXISTS "Error: Label '%s' already exists\n %s\n"
#define ERR_RESERVED_LABEL "Error: Label '%s' is a reserved keyword\n %s\n"
#define ERR_INVALID_LABEL "Error: Invalid label name '%s' \n %s\n"
#define ERR_LABEL_NOT_DEFINED "Error: Label '%s' is not defined\n %s\n"

#define ERR_CANNOT_ENTRY_EXTERN_LABEL "Error: Cannot .entry external label '%s'\n %s\n"
#define ERR_DIRECT_CANNOT_BE_MDEFINE "Error: Direct label cannot be an mdefine symbol"
#define BASE_LABEL_CANNOT_BE_MDEFINE "Error: Base label cannot be an mdefine symbol"
#define ERR_STRING_EXPECTS_ONE_STRING "Error: .string expects a single string\n %s\n"
#define ERR_EXPECTED_ZERO_OPERANDS "Error: Expected 0 operands\n %s\n"
#define ERR_EXPECTED_ONE_OPERAND "Error: Expected 1 operand\n %s\n"
#define ERR_EXPECTED_TWO_OPERANDS "Error: Expected 2 operands\n %s\n"
#define ERR_DEST_CANNOT_BE_IMMEDIATE "Error: Destination operand cannot be immediate\n %s\n"
#define ERR_SRC_CANNOT_BE_IMMEDIATE "Error: Source operand cannot be immediate\n %s\n"
#define ERR_SRC_CANNOT_BE_REGISTER "Error: Source operand cannot be register\n %s\n"
#define ERR_DEST_CANNOT_BE_INDEX "Error: Destination operand cannot be index\n %s\n"

#endif //ASSEMBLER_ERRORS_H
