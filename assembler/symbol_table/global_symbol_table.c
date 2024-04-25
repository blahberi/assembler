//
// Author: Eitan H.
//

#include "global_symbol_table.h"
#include "symbol_table.h"
#include <stdlib.h>

SymbolTable *SYMBOL_TABLE = NULL;
int init_global_symbol_table() {
    if (SYMBOL_TABLE){
        return 0;
    }
    SYMBOL_TABLE = construct_symbol_table();
    if (!SYMBOL_TABLE) {
        return -1;
    }
    return 0;
}

Symbol* symbol_table_find(const char *name) {
    return SYMBOL_TABLE->find(SYMBOL_TABLE, name);
}

void symbol_table_insert(Symbol *symbol) {
    SYMBOL_TABLE->insert(SYMBOL_TABLE, symbol);
}

bool symbol_table_is_in(const char *name) {
    return SYMBOL_TABLE->is_in(SYMBOL_TABLE, name);
}

typedef struct {
    int ic;
} UpdateContext;

void update_address(Symbol* symbol, UpdateContext* context) {
    int ic = context->ic;
    if (symbol->type == CODE_LABEL) {
        symbol->value += 100;
    } else if (symbol->type == DATA_LABEL) {
        symbol->value += 100 + ic;
    }
}

void symbol_table_update_address(int ic) {
    UpdateContext context = {ic};
    SYMBOL_TABLE->foreach(SYMBOL_TABLE, (void(*)(Symbol*, void*)) update_address, &context);
}

typedef struct {
    FILE* file;
} WriteContext;

void write_entry_file_helper(const Symbol* symbol, const WriteContext* context) {
    FILE* file = (FILE*)context->file;
    if (file == NULL) {
        return;
    }
    if (symbol->is_entry) {
        fprintf(file, "%s %04d\n", symbol->name, symbol->value);
    }
}

void write_entry_file(const char* filepath) {
    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Unable to open file %s\n", filepath);
        return;
    }

    WriteContext context = {file};
    SYMBOL_TABLE->foreach(SYMBOL_TABLE, (void (*)(Symbol*, void*)) write_entry_file_helper, &context);

    fclose(file);
}

void print_symbol(Symbol* symbol) {
    printf("Name: %s, Value: %d, Type: %d, Is Entry: %s\n",
           symbol->name,
           symbol->value,
           symbol->type,
           symbol->is_entry ? "Yes" : "No");
}

void symbol_table_print() {
    SYMBOL_TABLE->foreach(SYMBOL_TABLE, (void (*)(Symbol*, void*)) print_symbol, NULL);
}