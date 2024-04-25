/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_EXTERN_LABEL_USAGE_H
#define ASSEMBLER_EXTERN_LABEL_USAGE_H

/*
 * Whenever we use an external label in our assembly code,
 * we will store the address of the usage along side the label.
 * This is for the purpose of creating the .ext file for the linker.
 */
typedef struct { /* External label usage */
    char* label; /* The label */
    int memory_address; /* The memory address */
} ExternalLabelUsage;

ExternalLabelUsage* construct_external_label_usage(const char* label, int memory_address); /* Construct an external label usage */

#endif /* ASSEMBLER_EXTERN_LABEL_USAGE_H */
