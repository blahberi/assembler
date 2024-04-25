//
// Author: Eitan H.
//

#ifndef ASSEMBLER_EXTERN_HANDLER_H
#define ASSEMBLER_EXTERN_HANDLER_H

#include "extern_label_list.h"

void init_extern_list();
void add_extern_label_usage(const char *label, int memory_address);
ExternalLabelUsage *get_extern_label_usage(const char *label);
void free_extern_list();
void update_extern_list_address();
void write_extern_file(const char *filename);

#endif //ASSEMBLER_EXTERN_HANDLER_H
