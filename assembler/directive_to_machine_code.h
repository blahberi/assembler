/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_DIRECTIVE_TO_MACHINE_CODE_H
#define ASSEMBLER_DIRECTIVE_TO_MACHINE_CODE_H

int generate_data_directive(Context *context); /* Generate machine code for .data directive */
int generate_string_directive(Context *context); /* Generate machine code for .string directive */
int generate_entry_directive(Context *context); /* Mark symbol as entry. */
int generate_extern_directive(Context *context); /* Add symbol to symbol table as external. */

#endif /* ASSEMBLER_DIRECTIVE_TO_MACHINE_CODE_H */
