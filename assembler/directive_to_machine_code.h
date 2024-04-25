/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_DIRECTIVE_TO_MACHINE_CODE_H
#define ASSEMBLER_DIRECTIVE_TO_MACHINE_CODE_H

typedef struct context Context;

int generate_data_directive(Context *context);
int generate_string_directive(Context *context);
int generate_entry_directive(Context *context);
int generate_extern_directive(Context *context);

#endif /* ASSEMBLER_DIRECTIVE_TO_MACHINE_CODE_H */
