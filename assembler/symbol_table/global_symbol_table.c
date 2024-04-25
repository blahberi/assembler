/*
 Author: Eitan H.
*/

#include "global_symbol_table.h"
#include "symbol_table.h"
#include <stdlib.h>

SymbolTable *SYMBOL_TABLE = NULL;
int init_global_symbol_table() { /* Initialize the global symbol table */
    if (SYMBOL_TABLE){
        return 0;
    }
    SYMBOL_TABLE = construct_symbol_table();
    if (!SYMBOL_TABLE) {
        return -1;
    }
    return 0;
}

Symbol* symbol_table_find(const char *name) { /* Find a symbol in the table */
    return SYMBOL_TABLE->find(SYMBOL_TABLE, name);
}

void symbol_table_insert(Symbol *symbol) { /* Insert a symbol to the table */
    SYMBOL_TABLE->insert(SYMBOL_TABLE, symbol);
}

bool symbol_table_is_in(const char *name) {
    return SYMBOL_TABLE->is_in(SYMBOL_TABLE, name);
}

typedef struct {
    int ic;
} UpdateContext;

void update_address(Symbol* symbol, UpdateContext* context) { /* Update the address of a symbol */
    int ic = context->ic;
    if (symbol->type == CODE_LABEL) {
        symbol->value += 100;
    } else if (symbol->type == DATA_LABEL) {
        symbol->value += 100 + ic;
    }
}

void symbol_table_update_address(int ic) { /* Update the address of all symbols */
    UpdateContext context;
    context.ic = ic;
    SYMBOL_TABLE->foreach(SYMBOL_TABLE, (void(*)(Symbol*, void*)) update_address, &context);
}

void is_entry_helper(Symbol* symbol, bool* is_entry) { /* Check if a symbol is an entry */
    if (symbol->is_entry) {
        *((bool*)is_entry) = true;
    }
}

bool is_entry() { /* Check if there is an entry in the symbol table */
    bool is_entry = false;
    SYMBOL_TABLE->foreach(SYMBOL_TABLE, (void (*)(Symbol*, void*)) is_entry_helper, &is_entry);
    return is_entry;
}

typedef struct {
    FILE* file;
} WriteContext;

void write_entry_file_helper(const Symbol* symbol, const WriteContext* context) { /* callback function that writes a symbol to the .ent file if it's an entry Symbol */
    FILE* file = (FILE*)context->file;
    if (file == NULL) {
        return;
    }
    if (symbol->is_entry) {
        fprintf(file, "%s %04d\n", symbol->name, symbol->value);
    }
}

void write_entry_file(const char* filepath) { /* Write the .ent file */
    FILE* file;
    if (!is_entry()) {
        return;
    }
    file = fopen(filepath, "w");
    WriteContext context;

    if (file == NULL) {
        printf("Unable to open file %s\n", filepath);
        return;
    }
    context.file = file;
    SYMBOL_TABLE->foreach(SYMBOL_TABLE, (void (*)(Symbol*, void*)) write_entry_file_helper, &context);

    fclose(file);
}