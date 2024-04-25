/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_EXTERN_HANDLER_H
#define ASSEMBLER_EXTERN_HANDLER_H

#include "extern_label_list.h"

void init_extern_list(void); /* Initialize the extern list */
void add_extern_label_usage(const char *label, int memory_address); /* Add an external label usage */
ExternalLabelUsage *get_extern_label_usage(const char *label); /* Get an external label usage */
void free_extern_list(void); /* Free the extern list */
void update_extern_list_address(void); /* Update the addresses of the external labels */
void write_extern_file(const char *filepath); /* Write the extern file */

#endif /* ASSEMBLER_EXTERN_HANDLER_H */
