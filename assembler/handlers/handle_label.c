//
// Author: Eitan H.
//

#include "../assembler_context.h"
#include "../symbol_table/symbol.h"
#include "../symbol_table/global_symbol_table.h"
#include "../utils/error_checking.h"

int handle_label_instruction(const char* label, const char* line, const AssemblerContext* context) { // For instructions
    if (!context->is_first_pass){
        return -1;
    }
    if (check_label_err(line, label, context) != 0) {
        return -1;
    }
    Symbol *symbol = construct_symbol(label, CODE_LABEL, context->IC, false);
    symbol_table_insert(symbol);
    return 0;
}

int handle_label_data(const char* label, const char* line, const AssemblerContext* context){ // For .data and .string directives
    if (!context->is_first_pass){
        return -1;
    }
    if (check_label_err(line, label, context) != 0) {
        return -1;
    }
    Symbol *symbol = construct_symbol(label, DATA_LABEL, context->DC, false);
    symbol_table_insert(symbol);
    return 0;
}

int handle_label_extern(const char* label, const AssemblerContext* context) { // For .extern directive
    return 0;
}

int handle_label_entry(const char* label, const AssemblerContext *context) { // For .entry directive
    return 0;
}