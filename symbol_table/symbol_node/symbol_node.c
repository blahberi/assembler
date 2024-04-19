//
// Author: Eitan H. .
//

#include "symbol_node.h"
#include "../symbol/symbol.h"

#include <stdlib.h>
#include <string.h>

Symbol* find_symbol(SymbolNode* head, const char* name) {
    SymbolNode* node = head;
    while (node != NULL) {
        if (strcmp(node->symbol->name, name) == 0) {
            return node->symbol;
        }
        node = node->next;
    }
    return NULL;
}